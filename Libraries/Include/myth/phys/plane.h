
#pragma once

#include <myth\phys\shapes.h>

namespace myth
{
	namespace phys
	{

		//! [Primitive] Plane
		class __declspec(dllexport) Plane
		{
		public:
			//! Empty Constructor
			Plane() : m_odistance(0),m_normal(Normal(0,0,0)){}
			//! Initialization Constructor, Normal + Distance From Origin
			/*!
			\param normal The normal of the plane
			\param originDistance The distance the plane has from the origin in the direction of the normal
			*/
			Plane(Normal normal,float originDistance);
			//! Initialization Constructor, Normal + Point On Plane
			/*!
			\param normal The normal of the plane
			\param planePoint A point that lies on the plane
			*/
			Plane(Normal normal,Point planePoint);
			//! Initialization Constructor, Three Non-Collinear Points On Plane
			/*!
			\param A A point that lies on the plane that is not collinear with B and C
			\param B A point that lies on the plane that is not collinear with A and C
			\param C A point that lies on the plane that is not collinear with A and B
			*/
			Plane(Point A, Point B, Point C);

			//! Gets whether or not a point lies on the plane
			/*!
			\param point The point to be tested
			\return Returns a bool indicating whether or not the given point lies on the plane
			*/
			bool Intersects(Point point);

			//! Get the halfspace a point is located in
			/*!
			The plane divides the 3D space into two halfspaces, positive and negative. A point lies in the positive halfspace if it lies
			on the side towards which the planes normal points or on the plane, and in the negative region if it lies on the opposite side.

			\param point The point that we wish to test
			\return The halfspace (positive or negative) the point is located in
			*/
			bool GetHalfspace(Point point);

			//! Inverts the plane, flipping the normal
			/*!
			Inverts the planes normal, but does not change the area the plane occupies
			*/
			void Invert();

			Direction GetPlaneVectorA(){return GetOrthogonal3D(m_normal);}
			Direction GetPlaneVectorB(){return mCross(GetPlaneVectorA(),m_normal);}

			static Point ClosestPoint(const Normal& planeNormal, const float& originDistance, const Point& other);
			static Distance DistanceToPoint(const Normal& planeNormal, const float& originDistance, const Point& other);
			static Distance2 Distance2ToPoint(const Normal& planeNormal, const float& originDistance, const Point& other);
			static bool Contains(const Normal& planeNormal, const float& originDistance, const Point& other);

			static Point ClosestPoint(const Normal& planeNormal, const Point& pointOnPlane, const Point& other);
			static Distance DistanceToPoint(const Normal& planeNormal, const Point& pointOnPlane, const Point& other);
			static Distance2 Distance2ToPoint(const Normal& planeNormal, const Point& pointOnPlane, const Point& other);
			static bool Contains(const Normal& planeNormal, const Point& pointOnPlane, const Point& other);

			static Point ClosestPoint(const Point& pointA,const Point& pointB,const Point& pointC, const Point& other);
			static Distance DistanceToPoint(const Point& pointA,const Point& pointB,const Point& pointC,  const Point& other);
			static Distance2 Distance2ToPoint(const Point& pointA,const Point& pointB,const Point& pointC,  const Point& other);
			static bool Contains(const Point& pointA,const Point& pointB,const Point& pointC, const Point& other);

			//! Returns the point on the line that is closest to another point
			Point ClosestPoint(const Point& other) const{return Plane::ClosestPoint(m_normal,m_odistance,other);}
			//! Returns the distance of this line to another point
			Distance DistanceToPoint(const Point& other) const{return Plane::DistanceToPoint(m_normal,m_odistance,other);}
			//! Returns the distance of this line to another point squared
			Distance2 Distance2ToPoint(const Point& other) const{return Plane::Distance2ToPoint(m_normal,m_odistance,other);}
			//! Returns whether or not the point is located on the line
			bool Contains(const Point& other) const{return Plane::Contains(m_normal,m_odistance,other);}

			Normal m_normal;  //! The normal of the plane
			float m_odistance; //! Distance from the origin
		};
	}
}