
#pragma once

#include <myth\phys\shapes.h>

namespace myth
{
	namespace phys
	{
		//! [Primitive] Line Segment
		class __declspec(dllexport) LineSegment
		{
		public:
			//! Empty Constructor
			LineSegment() : m_startPoint(Point(0,0,0)),m_endPoint(Point(0,0,0)){}
			//! Initialization Constructor
			LineSegment(Point startPoint, Point endPoint);

			Point ClosestPointTemp(const Point& point) const;
			Distance DistanceTemp(const Point& point){return mLength(point - ClosestPointTemp(point));}


			static Point ClosestPoint(const Point& lineStart, const Point& lineEnd, const Point& other);
			static Distance DistanceToPoint(const Point& lineStart, const Point& lineEnd, const Point& other);
			static Distance2 Distance2ToPoint(const Point& lineStart, const Point& lineEnd, const Point& other);
			static bool Contains(const Point& lineStart, const Point& lineEnd, const Point& other);

			//! Returns the point on the line that is closest to another point
			Point ClosestPoint(const Point& other) const{return LineSegment::ClosestPoint(m_startPoint,m_endPoint,other);}
			//! Returns the distance of this line to another point
			Distance DistanceToPoint(const Point& other) const{return LineSegment::DistanceToPoint(m_startPoint,m_endPoint,other);}
			//! Returns the distance of this line to another point squared
			Distance2 Distance2ToPoint(const Point& other) const{return LineSegment::Distance2ToPoint(m_startPoint,m_endPoint,other);}
			//! Returns whether or not the point is located on the line
			bool Contains(const Point& other) const{return LineSegment::Contains(m_startPoint,m_endPoint,other);}

			Point m_startPoint;
			Point m_endPoint;
		};
	}
}