
#pragma once

#include <myth\phys\shapes.h>

namespace myth
{
	namespace phys
	{
		//! [Primitive] Line
		class __declspec(dllexport) Line
		{
		public:
			//! Empty Constructor
			Line() : m_startPoint(Point(0,0,0)),m_endPoint(Point(0,0,0)){}
			//! Initialization Constructor
			Line(Point startPoint, Point endPoint);

			static Point ClosestPoint(const Point& lineStart, const Point& lineEnd, const Point& other);
			static Distance DistanceToPoint(const Point& lineStart, const Point& lineEnd, const Point& other);
			static Distance2 Distance2ToPoint(const Point& lineStart, const Point& lineEnd, const Point& other);
			static bool Contains(const Point& lineStart, const Point& lineEnd, const Point& other);

			//! Returns the point on the line that is closest to another point
			Point ClosestPoint(const Point& other) const{return Line::ClosestPoint(m_startPoint,m_endPoint,other);}
			//! Returns the distance of this line to another point
			Distance DistanceToPoint(const Point& other) const{return Line::DistanceToPoint(m_startPoint,m_endPoint,other);}
			//! Returns the distance of this line to another point squared
			Distance2 Distance2ToPoint(const Point& other) const{return Line::Distance2ToPoint(m_startPoint,m_endPoint,other);}
			//! Returns whether or not the point is located on the line
			bool Contains(const Point& other) const{return Line::Contains(m_startPoint,m_endPoint,other);}

			Point m_startPoint;
			Point m_endPoint;
		};
	}
}