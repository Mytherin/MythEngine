
#include <myth\debug\assert.h>
#include <myth\debug\assertfunctions.h>
#include <myth\phys\aabb.h>
#include <myth\phys\ray.h>
#include <myth\phys\sphere.h>

using myth::phys::AABB;
using myth::phys::Distance;
using myth::phys::Distance2;
using myth::phys::Point;
using myth::phys::Ray;
using myth::phys::Size;
using myth::phys::Sphere;

AABB::AABB(Point center, Size size) 
	: m_center(center),m_size(size),IBoundingVolume(type_AABB)
{
	Assert(NotNull(m_size),L"DEGENERATE AABB ERROR: Attempting to create an AABB that has a size of 0 in some dimension.");
}

AABB::AABB(float minx, float miny, float minz, float maxx, float maxy, float maxz) : 
	m_center((Point(minx,miny,minz) + Point(maxx,maxy,maxz))*0.5f),
	m_size((Point(maxx,maxy,maxz) - Point(minx,miny,minz))*0.5f),IBoundingVolume(type_AABB)
{
	Assert(NotNull(m_size),L"DEGENERATE AABB ERROR: Attempting to create an AABB that has a size of 0 in some dimension, are the minimal and maximum values identical?");
}

bool AABB::Intersects(const AABB& other) const
{
	Assert(NotNull(m_size),L"DEGENERATE AABB ERROR: The AABB has a size of 0, did you initialize the AABB?");
	return 
		abs(m_center.x - other.m_center.x) <= (m_size.x + other.m_size.x) &&
		abs(m_center.z - other.m_center.z) <= (m_size.z + other.m_size.z) &&
		abs(m_center.y - other.m_center.y) <= (m_size.y + other.m_size.y);	
}

bool AABB::Intersects(const Point& other) const
{
	return Contains(other);
}

bool AABB::Intersects(const Ray& other) const
{
	Assert(NotNull(m_size),L"DEGENERATE AABB ERROR: The AABB has a size of 0, did you initialize the AABB?");
	return true;
}

bool AABB::Intersects(const Sphere& other) const
{
	Assert(NotNull(m_size),L"DEGENERATE AABB ERROR: The AABB has a size of 0, did you initialize the AABB?");
	Offset d = other.m_center - ClosestPoint(other.m_center); //get the vector from the sphere to the closest point on the AABB to the sphere
	float distSq = glm::dot(d,d);                            //a dot of a vector with itself is its length squared
	return distSq <= (other.m_radius * other.m_radius);      //check if length squared is smaller than distance squared
} 

Point AABB::ClosestPoint(const Point& c, const Size& s, const Point& o)
{
	Assert(NotNull(s),L"DEGENERATE AABB ERROR: The AABB has a size of 0, did you initialize the AABB?");
	return Point(
		myth::math::clamp(o.x,c.x-s.x,c.x+s.x),
		myth::math::clamp(o.y,c.y-s.y,c.y+s.y),
		myth::math::clamp(o.z,c.z-s.z,c.z+s.z));
}

Distance AABB::DistanceToPoint(const Point& c, const Size& s, const Point& o)
{
	return sqrt(Distance2ToPoint(c,s,o));
}

Distance2 AABB::Distance2ToPoint(const Point& c, const Size& s, const Point& o)
{
	Assert(NotNull(s),L"DEGENERATE AABB ERROR: The AABB has a size of 0, did you initialize the AABB?");

	float dist = 0.0f;

	for(int i = 0; i < 3; ++i)
	{
		if (o[i] < (c[i] - s[i])) 
			dist += ((c[i] - s[i]) - o[i]) * ((c[i] - s[i]) - o[i]);
		if (o[i] > (c[i] + s[i])) 
			dist += (o[i] - (c[i] + s[i])) * (o[i] - (c[i] + s[i]));
	}

	return dist;
}

bool AABB::Contains(const Point& c, const Size& s, const Point& o)
{
	Assert(NotNull(s),L"DEGENERATE AABB ERROR: The AABB has a size of 0, did you initialize the AABB?");
	return 
		o.x >= c.x - s.x &&
		o.x <= c.x + s.x &&
		o.z >= c.z - s.z &&
		o.z <= c.z + s.z &&
		o.y >= c.y - s.y &&
		o.y <= c.y + s.y;
}
