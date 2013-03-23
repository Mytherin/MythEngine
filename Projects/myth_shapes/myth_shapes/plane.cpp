
#include <myth\debug\assert.h>
#include <myth\debug\assertfunctions.h>
#include <myth\phys\plane.h>

using myth::phys::Distance;
using myth::phys::Distance2;
using myth::phys::Normal;
using myth::phys::Plane;
using myth::phys::Point;

Plane::Plane(Normal normal,float originDistance) 
	: m_normal(normal),m_odistance(originDistance)
{
	Assert(IsNormal(m_normal),L"DEGENERATE PLANE ERROR: Attempting to create a plane with a normal that is not a unit vector (length 1)");
}

Plane::Plane(Normal normal,Point planePoint) 
	: m_normal(normal),m_odistance(glm::dot(m_normal,planePoint))
{
	Assert(IsNormal(m_normal),L"DEGENERATE PLANE ERROR: Attempting to create a plane with a normal that is not a unit vector (length 1)");
}


Plane::Plane(Point A, Point B, Point C) : m_normal(mNormalize(mCross(B - A, C - A))),m_odistance(mDot(m_normal,A))
{
	Assert(AreInequal(A,B,C),L"DEGENERATE PLANE ERROR: Attempting to create a plane with three non-unique points (points are equal to another)");
	Assert(AreNotCollinear(A,B,C),L"DEGENERATE PLANE ERROR: Attempting to create a plane with three collinear points (points lie on the same line)");
}

bool Plane::Intersects(Point point)
{
	Assert(IsNormal(m_normal),L"DEGENERATE PLANE ERROR: The plane's normal is not of length 1. Has the plane been initialized?");
	return (mDot(m_normal,point) == m_odistance);
}

bool Plane::GetHalfspace(Point point)
{
	Assert(IsNormal(m_normal),L"DEGENERATE PLANE ERROR: The plane's normal is not of length 1. Has the plane been initialized?");

	return (mDot(m_normal,point) >= m_odistance);
}

void Plane::Invert()
{
	m_normal *= -1;
	m_odistance *= -1;
}

//normal + offset from origin plane
Point Plane::ClosestPoint(const Normal& n, const float& od, const Point& o)
{
	Assert(IsNormal(n),L"DEGENERATE PLANE ERROR: The plane's normal is not of length 1. Has the plane been initialized?");

	Offset toPoint = o - (n * od);
	float dist = mDot(n,toPoint);

	return o - dist * n;
}

Distance Plane::DistanceToPoint(const Normal& n, const float& od, const Point& o)
{
	return mDot(n,o) + od;
}

Distance2 Plane::Distance2ToPoint(const Normal& n, const float& od, const Point& o)
{
	float dist = DistanceToPoint(n,od,o);
	return dist * dist;
}

bool Plane::Contains(const Normal& n, const float& od, const Point& o)
{
	return DistanceToPoint(n,od,o) == 0;
}


//normal + point plane
Point Plane::ClosestPoint(const Normal& n, const Point& a, const Point& o)
{
	Assert(IsNormal(n),L"DEGENERATE PLANE ERROR: The plane's normal is not of length 1. Has the plane been initialized?");

	Offset toPoint = o - a;
	float dist = mDot(n,toPoint);

	return o - dist * n;
}

Distance Plane::DistanceToPoint(const Normal& n, const Point& a, const Point& o)
{
	Offset toPoint = o - a;
	return mDot(n,toPoint);
}

Distance2 Plane::Distance2ToPoint(const Normal& n, const Point& a, const Point& o)
{
	float dist = DistanceToPoint(n,a,o);
	return dist * dist;
}

bool Plane::Contains(const Normal& n, const Point& a, const Point& o)
{
	return DistanceToPoint(n,a,o) == 0;
}


//three point plane
Point Plane::ClosestPoint(const Point& a, const Point& b, const Point& c, const Point& o)
{
	Assert(AreInequal(a,b,c),L"DEGENERATE PLANE ERROR: Attempting to create a plane with three non-unique points (points are equal to another)");
	Assert(AreNotCollinear(a,b,c),L"DEGENERATE PLANE ERROR: Attempting to create a plane with three collinear points (points lie on the same line)");
	
	Normal n = mNormalize(mCross(b - a, c - a));
	Offset toPoint = o - a;
	float dist = mDot(n,toPoint);

	return o - dist * n;
}

Distance Plane::DistanceToPoint(const Point& a, const Point& b, const Point& c, const Point& o)
{
	Normal n = mNormalize(mCross(b - a, c - a));
	Offset toPoint = o - a;
	return mDot(n,toPoint);
}

Distance2 Plane::Distance2ToPoint(const Point& a, const Point& b, const Point& c, const Point& o)
{
	float dist = DistanceToPoint(a,b,c,o);
	return dist * dist;
}

bool Plane::Contains(const Point& a, const Point& b, const Point& c, const Point& o)
{
	return DistanceToPoint(a,b,c,o) == 0;
}