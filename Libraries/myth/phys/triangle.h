
#pragma once

#include <myth\phys\shapes.h>

namespace myth
{
	namespace phys
	{
		//! [Primitive] Triangle
		class __declspec(dllexport) Triangle
		{
		public:
			//! Empty Constructor
			Triangle() : m_pointA(Point(0,0,0)),m_pointB(Point(0,0,0)),m_pointC(Point(0,0,0)){}
			//! Initialization Constructor
			Triangle(Point A, Point B, Point C);

			void Create(Point A, Point B, Point C);

			static Point ClosestPoint(const Point& A, const Point& B,const Point& C, const Point& other);
			static Distance DistanceToPoint(const Point& A, const Point& B,const Point& C, const Point& other);
			static Distance2 Distance2ToPoint(const Point& A, const Point& B,const Point& C, const Point& other);
			static bool Contains(const Point& A, const Point& B,const Point& C, const Point& other);

			//! Returns the point on the triangle that is closest to another point
			Point ClosestPoint(const Point& other) const { 	return Triangle::ClosestPoint(m_pointA,m_pointB,m_pointC,other); }
			//! Returns the distance of this triangle to another point
			Distance DistanceToPoint(const Point& other) const { return Triangle::DistanceToPoint(m_pointA,m_pointB,m_pointC,other); }
			//! Returns the distance of this triangle to another point squared
			Distance2 Distance2ToPoint(const Point& other) const { return Triangle::Distance2ToPoint(m_pointA,m_pointB,m_pointC,other);}
			//! Returns whether or not the point is located on the triangle
			bool Contains(const Point& other) const	{return Triangle::Contains(m_pointA,m_pointB,m_pointC,other);}

			Point m_pointA;
			Point m_pointB;
			Point m_pointC;
		};
	}
}