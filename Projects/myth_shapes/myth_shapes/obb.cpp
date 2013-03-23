

#include <myth\debug\assert.h>
#include <myth\debug\assertfunctions.h>
#include <myth\phys\aabb.h>
#include <myth\phys\obb.h>
#include <myth\phys\ray.h>
#include <myth\phys\sphere.h>

using myth::phys::AABB;
using myth::phys::Distance;
using myth::phys::Distance2;
using myth::phys::OBB;
using myth::phys::Point;
using myth::phys::Ray;
using myth::phys::Rotation;
using myth::phys::Size;
using myth::phys::Sphere;

OBB::OBB(Point center, Size size, Rotation rotation) 
	: m_size(size),m_center(center),m_rotation(rotation),IBoundingVolume(type_OBB)
{
	Assert(NotNull(m_size),L"DEGENERATE OBB ERROR: Attempting to create an OBB that has a size of 0 in some dimension.");
}

bool OBB::Intersects(const AABB& other) const
{
	return true;
}

bool OBB::Intersects(const Point& other) const
{
	return Contains(m_center,m_size,m_rotation,other);
}

bool OBB::Intersects(const Sphere& other) const
{
	return true;
}

bool OBB::Intersects(const Ray& other) const
{
	return true;
}


Point OBB::ClosestPoint(const Point& c, const Size& s, const Rotation& r,const Point& o)
{
	Assert(NotNull(s),L"DEGENERATE OBB ERROR: The OBB has a size of 0. Did you initialize the OBB?");
	Point projectedPoint = o - c;            //project the point to OBB-space by subtracting the OBB's center, effectively making the OBB's center the origin
	Point closest = c;                       //set the initial closest point to the origin (the center of the OBB)

	AxisRotation u;
	for(unsigned int i = 0; i < 3; ++i)      //now project the point onto the three axis created by the rotated OBB as you would with a line segment
	{
		u = r[i];                           //we will clamp the value to the edges of the box as we would with an AABB
		float dist = mDot(projectedPoint,u); //get how far the point is along the line segment of the current axis
		 
		if (dist > s[i]) dist = s[i];       //if it lies outisde the OBB to the negative side, clamp it to the bottom
		if (dist < -s[i]) dist = -s[i];     //if it lies outside of the OBB to the positive side, clamp it to the top

		closest += dist * u;                //otherwise grab the value within the OBB closest to 
	}

	return closest;
}

Distance OBB::DistanceToPoint(const Point& c, const Size& s, const Rotation& r,const Point& o)
{
	return sqrt(Distance2ToPoint(c,s,r,o));
}

Distance2 OBB::Distance2ToPoint(const Point& c, const Size& s,const Rotation& r, const Point& o)
{
	Assert(NotNull(s),L"DEGENERATE OBB ERROR: The OBB has a size of 0. Did you initialize the OBB?");
	Point projectedPoint = o - c;       
	float sqDist = 0;                     

	AxisRotation u;
	for(unsigned int i = 0; i < 3; ++i)      
	{
		u = r[i];                           
		float dist = mDot(projectedPoint,u); 
		 
		if (dist < -s[i]) sqDist += (dist + s[i]) * (dist + s[i]);     
		else if (dist > s[i]) sqDist += (dist - s[i]) * (dist - s[i]);  
	}
	return sqDist;
}

bool OBB::Contains(const Point& c, const Size& s, const Rotation& r, const Point& o)
{
	return (Distance2ToPoint(c,s,r,o) == 0);
}
