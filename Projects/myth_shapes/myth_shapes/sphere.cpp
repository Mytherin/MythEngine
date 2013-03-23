
#include <myth\debug\assert.h>
#include <myth\debug\assertfunctions.h>
#include <myth\phys\aabb.h>
#include <myth\phys\ray.h>
#include <myth\phys\sphere.h>

using myth::phys::AABB;
using myth::phys::Point;
using myth::phys::Ray;
using myth::phys::Sphere;

Sphere::Sphere(Point center, float radius) : m_radius(radius),m_center(center),IBoundingVolume(type_SPHERE)
{
	Assert(m_radius != 0,L"DEGENERATE SPHERE ERROR: Attempting to create a sphere with a radius of 0.");
}

Sphere::Sphere(const Point& A, const Point& B) : IBoundingVolume(type_SPHERE)
{
	Create(A,B);
}

Sphere::Sphere(const Point& A, const Point& B, const Point& C) : IBoundingVolume(type_SPHERE)
{
	Create(A,B,C);
}

Sphere::Sphere(const Point& A, const Point& B, const Point& C, const Point& D) : IBoundingVolume(type_SPHERE)
{
	Create(A,B,C,D);
}

void Sphere::Create(const Point& A)
{
	m_radius = 0;
	m_center = A;
}

void Sphere::Create(const Point& A, const Point& B)
{
	Assert(AreInequal(A,B),L"DEGENERATE SPHERE ERROR: Attempting to create a sphere with two identical points.");
	
	Offset off = (B - A)/2.0f;
	m_radius = glm::length(off);
	m_center = A + off;
}

void Sphere::Create(const Point& A, const Point& B, const Point& C)
{
	Assert(AreInequal(A,B,C),L"DEGENERATE SPHERE ERROR: Attempting to create a sphere with two identical points.");
	Assert(AreNotCollinear(A,B,C),L"DEGENERATE SPHERE ERROR: Attempting to create a sphere with three collinear points.");
	
	Point a = B - A;
	Point b = C - A;

	Point crossab = glm::cross(a,b);

	float denominator = 2.0f * glm::dot(crossab, crossab);

	Point offset = (
		(glm::dot(b,b) * glm::cross(crossab,a)) + 
		(glm::dot(a,a) * glm::cross(b,crossab))) 
		/ denominator;

	m_radius = glm::length(offset);
	m_center = A + offset;
}

void Sphere::Create(const Point& A, const Point& B, const Point& C, const Point& D)
{
	Assert(AreInequal(A,B,C,D),L"DEGENERATE SPHERE ERROR: Attempting to create a sphere with two identical points.");
	Assert(AreNotCollinear(A,B,C,D),L"DEGENERATE SPHERE ERROR: Attempting to create a sphere with three collinear points.");

	Point a = B - A;
	Point b = C - A;
	Point c = D - A;

	float Denominator = 2.0f * glm::determinant(glm::mat3(a.x, a.y, a.z,b.x, b.y, b.z,c.x, c.y, c.z));

	if (Denominator == 0)
	{
		int x = 5;
	}

	Point offset = (
		(glm::dot(c,c)) * (glm::cross(a,b)) +
		(glm::dot(b,b)) * (glm::cross(c,a)) +
		(glm::dot(a,a)) * (glm::cross(b,c))) / Denominator;

	m_radius = glm::length(offset);
	m_center = A + offset;
}




bool Sphere::Intersects(const AABB& other) const
{
	Assert(m_radius != 0,L"DEGENERATE SPHERE ERROR: The sphere has a radius of 0, did you initialize the sphere?");
	return other.Intersects(*this);
}

bool Sphere::Intersects(const Point& other) const
{
	Assert(m_radius != 0,L"DEGENERATE SPHERE ERROR: The sphere has a radius of 0, did you initialize the sphere?");
	Offset d = (other - m_center);
	float distSq = glm::dot(d,d);
	return distSq <= m_radius * m_radius;
}

bool Sphere::Intersects(const Ray& other) const
{
	Assert(m_radius != 0,L"DEGENERATE SPHERE ERROR: The sphere has a radius of 0, did you initialize the sphere?");
	return true;
}

bool Sphere::Intersects(const Sphere& other) const
{
	Assert(m_radius != 0,L"DEGENERATE SPHERE ERROR: The sphere has a radius of 0, did you initialize the sphere?");
	Offset d = other.m_center - m_center;                                            //get the offset between the two spheres
	float distSq = glm::dot(d,d);                                                    //a dot of a vector with itself is its length squared
	return distSq <= (other.m_radius + m_radius) * (other.m_radius + m_radius);      //check if length squared is smaller than distance squared
}

