
#pragma once

#include <myth\phys\shapes.h>

namespace myth
{
	namespace phys
	{
		//! [Primitive] Tetrahedron
		class __declspec(dllexport) Tetrahedron
		{
		public:
			//! Empty Constructor
			Tetrahedron() : m_pointA(Point(0,0,0)),m_pointB(Point(0,0,0)),m_pointC(Point(0,0,0)),m_pointD(Point(0,0,0)){}
			//! Initialization Constructor
			Tetrahedron(Point A, Point B,Point C, Point D);

			void Create(Point A, Point B,Point C, Point D);

			static Point ClosestPoint(const Point& A, const Point& B,const Point& C,const Point& D, const Point& other);
			static Distance DistanceToPoint(const Point& A, const Point& B,const Point& C,const Point& D, const Point& other);
			static Distance2 Distance2ToPoint(const Point& A, const Point& B,const Point& C,const Point& D, const Point& other);
			static bool Contains(const Point& A, const Point& B,const Point& C,const Point& D, const Point& other);

			//! Returns the point on the triangle that is closest to another point
			Point ClosestPoint(const Point& other) const { 	return Tetrahedron::ClosestPoint(m_pointA,m_pointB,m_pointC,m_pointD,other); }
			//! Returns the distance of this triangle to another point
			Distance DistanceToPoint(const Point& other) const { return Tetrahedron::DistanceToPoint(m_pointA,m_pointB,m_pointC,m_pointD,other); }
			//! Returns the distance of this triangle to another point squared
			Distance2 Distance2ToPoint(const Point& other) const { return Tetrahedron::Distance2ToPoint(m_pointA,m_pointB,m_pointC,m_pointD,other);}
			//! Returns whether or not the point is located on the triangle
			bool Contains(const Point& other) const	{return Tetrahedron::Contains(m_pointA,m_pointB,m_pointC,m_pointD,other);}

			Point m_pointA;
			Point m_pointB;
			Point m_pointC;
			Point m_pointD; 
		};
	}
}