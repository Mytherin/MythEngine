
#pragma once

#include <myth\phys\shapes.h>

namespace myth
{
	namespace phys
	{
		class Simplex
		{
		public:
			Simplex() : m_elements(0){}
			Simplex(Point A);
			Simplex(Point A,Point B);
			Simplex(Point A,Point B, Point C);
			Simplex(Point A,Point B, Point C, Point D);

			void Create(Point A);
			void Create(Point A, Point B);
			void Create(Point A, Point B, Point C);
			void Create(Point A, Point B, Point C, Point D);

			//! Expands a simplex with a new point, creating a new simplex that contains the point and returning a direction to to the origin
			/*!
			The expand simplex routine is used in the GJK algorithm to expand a simplex 
			*/
			Direction Expand(const Point& O);

			char m_elements;
			Point m_points[4];
		private:
			//! Expand a simplex with 0 elements (m_elements = 0)
			Direction Expand0(const Point& A);
			//! Expand a simplex with 1 element (m_elements = 1)
			Direction Expand1(const Point& B, const Point& A);
			//! Expand a simplex with 2 elements (m_elements = 2)
			Direction Expand2(const Point& B, const Point& C, const Point& A);
			//! Expand a simplex with 3 elements (m_elements = 3)
			Direction Expand3(const Point& B, const Point& C, const Point& D, const Point& A);
		};
	}
}