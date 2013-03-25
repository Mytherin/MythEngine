
#pragma once

#include <myth\phys\shapes.h>

namespace myth
{
	namespace phys
	{
		//! [Primitive] Ray
		class __declspec(dllexport) Ray
		{
		public:
			//! Empty Constructor
			Ray() : m_startPoint(Point(0,0,0)),m_endPoint(Point(0,0,0)){}
			//! Initialization Constructor
			Ray(Point startPoint, Point otherPoint);

			static Point ClosestPoint(const Point& lineStart, const Point& lineEnd, const Point& other);
			static Distance DistanceToPoint(const Point& lineStart, const Point& lineEnd, const Point& other);
			static Distance2 Distance2ToPoint(const Point& lineStart, const Point& lineEnd, const Point& other);
			static bool Contains(const Point& lineStart, const Point& lineEnd, const Point& other);

			//! Returns the point on the line that is closest to another point
			Point ClosestPoint(const Point& other) const{return Ray::ClosestPoint(m_startPoint,m_endPoint,other);}
			//! Returns the distance of this line to another point
			Distance DistanceToPoint(const Point& other) const{return Ray::DistanceToPoint(m_startPoint,m_endPoint,other);}
			//! Returns the distance of this line to another point squared
			Distance2 Distance2ToPoint(const Point& other) const{return Ray::Distance2ToPoint(m_startPoint,m_endPoint,other);}
			//! Returns whether or not the point is located on the line
			bool Contains(const Point& other) const{return Ray::Contains(m_startPoint,m_endPoint,other);}

			Point m_startPoint;
			Point m_endPoint; 
		};
	}
}