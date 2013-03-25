
#pragma once

#include <myth\phys\shapes.h>

namespace myth
{
	namespace phys
	{
		//! [Primitive] Rectangle
		/*!
		A rectangle is defined by its three corner points similar to a triangle. The rectangle is defined as 
		A + u(B - A) + y(C-A) with u and y = [0..1], so the four corners of the rectangle are A; A + (B - A); A + (C - A); A + (B - A) + (C - A)
		*/
		class __declspec(dllexport) Rectangle
		{
		public:
			//! Empty Constructor
			Rectangle() : m_pointA(Point(0,0,0)),m_pointB(Point(0,0,0)),m_pointC(Point(0,0,0)){}
			//! Initialization Constructor
			Rectangle(Point pointA, Point pointB, Point pointC);

			static Point ClosestPoint(const Point& pointA, const Point& pointB,const Point& pointC, const Point& other);
			static Distance DistanceToPoint(const Point& pointA, const Point& pointB,const Point& pointC, const Point& other);
			static Distance2 Distance2ToPoint(const Point& pointA, const Point& pointB,const Point& pointC, const Point& other);
			static bool Contains(const Point& pointA, const Point& pointB,const Point& pointC, const Point& other);

			//! Returns the point on the rectangle that is closest to another point
			Point ClosestPoint(const Point& other) const { 	return Rectangle::ClosestPoint(m_pointA,m_pointB,m_pointC,other); }
			//! Returns the distance of this rectangle to another point
			Distance DistanceToPoint(const Point& other) const { return Rectangle::DistanceToPoint(m_pointA,m_pointB,m_pointC,other); }
			//! Returns the distance of this rectangle to another point squared
			Distance2 Distance2ToPoint(const Point& other) const { return Rectangle::Distance2ToPoint(m_pointA,m_pointB,m_pointC,other);}
			//! Returns whether or not the point is located on the rectangle
			bool Contains(const Point& other) const	{return Rectangle::Contains(m_pointA,m_pointB,m_pointC,other);}

			Point m_pointA;
			Point m_pointB; 
			Point m_pointC; 
		};
	}
}