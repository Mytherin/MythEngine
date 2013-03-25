
#pragma once

#include <myth\phys\iboundingvolume.h>

namespace myth
{
	namespace phys
	{
		namespace 
		{
			//! constant ratio used in sphere area calculation, 4/3 * pi
			const float area_constant = (float)(4.0 / 3.0 * 3.14159265);
		}

		//! [Bounding Volume] Bounding Sphere
		class __declspec(dllexport) Sphere : public IBoundingVolume
		{
		public:
			//! Empty Constructor
			Sphere() : m_radius(0),m_center(Point(0,0,0)),IBoundingVolume(type_SPHERE){}
			//! Initialization Constructor
			Sphere(Point center, float radius);

			//! Initialization Constructor, Create a minimal sphere containing one point
			Sphere(const Point& A) : m_radius(0), m_center(A), IBoundingVolume(type_SPHERE){}
			//! Initialization constructor, create a minimal sphere with two points on the edge
			Sphere (const Point& A, const Point& B);
			//! Initialization constructor, create a minimal sphere with three points on the edge
			Sphere (const Point& A, const Point& B, const Point& C);
			//! Initialization constructor, create a minimal sphere with four points on the edge. 
			Sphere (const Point& A, const Point& B, const Point& C, const Point& D);

			//! Create a minimal sphere with point A on the edge of the sphere
			void Create(const Point& A);
			//! Create a minimal sphere with points A and B on the edge of the sphere
			void Create(const Point& A, const Point& B);
			//! Create a minimal sphere with points A, B and C on the edge of the sphere
			void Create(const Point& A, const Point& B, const Point& C);
			//! Create a minimal sphere with points A,B,C and D on the edge of the sphere
			void Create(const Point& A, const Point& B, const Point& C, const Point& D);

			//! Sphere - AABB Intersection
			bool Intersects(const AABB& other) const;
			//! Sphere - Point Intersection
			bool Intersects(const Point& other) const;
			//! Sphere - Ray Intersection
			bool Intersects(const Ray& other) const;
			//! Sphere - Sphere Intersection
			bool Intersects(const Sphere& other) const;

			//! Volume that the sphere occupies
			/*!
			The volume is computed with 4/3 * pi * radius^3.
			\return Returns the volume the sphere occupies
			*/
			Volume Volume() const
			{
				return area_constant * m_radius * m_radius * m_radius;
			}

			float m_radius;
			Point m_center; 
		};
	}
}