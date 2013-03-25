
#pragma once

#include <myth\phys\iboundingvolume.h>
#include <myth\phys\rotation.h>

namespace myth
{
	namespace phys
	{
		//! [Bounding Volume] Oriented Bounding Box
		class __declspec(dllexport) OBB : public IBoundingVolume
		{
		public:
			//! Empty Constructor
			OBB() : m_size(Size(0,0,0)),m_center(Point(0,0,0)),m_rotation(Rotation()),IBoundingVolume(type_OBB){}
			//! Initialization Constructor, Center Point, Half-Widths, Orientation
			OBB(Point center, Size size, Rotation rotation);

			//! OBB - AABB Intersection
			bool Intersects(const AABB& other) const;
			//! OBB - Point Intersection
			bool Intersects(const Point& other) const;
			//! OBB - Ray Intersection
			bool Intersects(const Ray& other) const;
			//! OBB - Sphere Intersection
			bool Intersects(const Sphere& other) const;

			AABB BoundingAABB();

			static Point ClosestPoint(const Point& center, const Size& halfwidths, const Rotation& rotation,const Point& other);
			static Distance DistanceToPoint(const Point& center, const Size& halfwidths, const Rotation& rotation,const Point& other);
			static Distance2 Distance2ToPoint(const Point& center, const Size& halfwidths,const Rotation& rotation, const Point& other);
			static bool Contains(const Point& center, const Size& halfwidths, const Rotation& rotation, const Point& other);

			//! Returns the point on the line that is closest to another point
			Point ClosestPoint(const Point& other) const { return OBB::ClosestPoint(m_center,m_size,m_rotation,other); }
			//! Returns the distance of this line to another point
			Distance DistanceToPoint(const Point& other) const { return OBB::DistanceToPoint(m_center,m_size,m_rotation,other); }
			//! Returns the distance of this line to another point squared
			Distance2 Distance2ToPoint(const Point& other) const { return OBB::Distance2ToPoint(m_center,m_size,m_rotation,other); }
			//! Returns whether or not the point is located on the line
			bool Contains(const Point& other) const { return OBB::Contains(m_center,m_size,m_rotation,other); }

			//! The volume that the OBB occupies
			/*!
			\return Returns the volume the OBB occupies, computed by width*length*height
			*/
			Volume Volume()
			{
				return 8 * m_size.x * m_size.y * m_size.z;
			}

			//! The orientation of the OBB
			Rotation m_rotation;
			//! The center point of the OBB
			Point m_center; 
			//! The half-widths of the OBB
			Size m_size;
		};
	}
}