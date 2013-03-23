
#pragma once

#include <myth\phys\iboundingvolume.h>

namespace myth
{
	namespace phys
	{
		//! [Bounding Volume] Axis-Aligned Bounding Box
		class __declspec(dllexport) AABB : public IBoundingVolume
		{
		public:
			//! Empty Constructor
			AABB() : m_center(Point(0,0,0)),m_size(Size(0,0,0)),IBoundingVolume(type_AABB){}
			//! Initialization Constructor, Center-Point, Half-Widths
			AABB(Point center, Size size);
			//! Initialization Constructor, Min-Point, Max-Point
			AABB(float minx, float miny, float minz, float maxx, float maxy, float maxz);

			//! AABB - AABB Intersection
			bool Intersects(const AABB& other) const;
			//! AABB - Point Intersection
			bool Intersects(const Point& other) const;
			//! AABB - Polyhedron Intersection
			bool Intersects(const Polyhedron& other) const;
			//! AABB - Ray Intersection
			bool Intersects(const Ray& other) const;
			//! AABB - Sphere Intersection
			bool Intersects(const Sphere& other) const;

			static Point ClosestPoint(const Point& center, const Size& halfwidths, const Point& other);
			static Distance DistanceToPoint(const Point& center, const Size& halfwidths, const Point& other);
			static Distance2 Distance2ToPoint(const Point& center, const Size& halfwidths, const Point& other);
			static bool Contains(const Point& center, const Size& halfwidths, const Point& other);

			//! Returns the point on the line that is closest to another point
			Point ClosestPoint(const Point& other) const{return AABB::ClosestPoint(m_center,m_size,other);}
			//! Returns the distance of this line to another point
			Distance DistanceToPoint(const Point& other) const{return AABB::DistanceToPoint(m_center,m_size,other);}
			//! Returns the distance of this line to another point squared
			Distance2 Distance2ToPoint(const Point& other) const{return AABB::Distance2ToPoint(m_center,m_size,other);}
			//! Returns whether or not the point is located on the line
			bool Contains(const Point& other) const{return AABB::Contains(m_center,m_size,other);}

			//! The volume that the AABB occupies
			/*!
			\return Returns the volume the AABB occupies, computed by width*length*height
			*/
			Volume Volume() const
			{
				return 8 * m_size.x * m_size.y * m_size.z; //the SIZE contains only half-sizes (the radius), thus we multiply by 8 (2*2*2)
			}

			//! The center point of the AABB
			Point m_center; 
			//! The half-widths of the AABB
			Size m_size;
		};
	}
}