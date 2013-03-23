
#include <myth\debug\assert.h>
#include <myth\debug\assertfunctions.h>
#include <myth\phys\plane.h>
#include <myth\phys\tetrahedron.h>
#include <gtx\norm.hpp>

using myth::phys::Distance;
using myth::phys::Distance2;
using myth::phys::Offset;
using myth::phys::Plane;
using myth::phys::Point;
using myth::phys::Tetrahedron;

Tetrahedron::Tetrahedron(Point pointA, Point pointB,Point pointC, Point pointD) 
	: m_pointA(pointA),m_pointB(pointB),m_pointC(pointC),m_pointD(pointD)
{
	Assert(AreInequal(m_pointA,m_pointB,m_pointC,m_pointD),L"DEGENERATE TETRAHEDRON ERROR: Attempting to create a tetrahedron with four non-unique points (points are equal to another)");
	Assert(AreNotCollinear(m_pointA,m_pointB,m_pointC,m_pointD),L"DEGENERATE TETRAHEDRON ERROR: Attempting to create a tetrahedron with three collinear points (they lie on the same line).");
	Assert(AreNotCoplanar(m_pointA,m_pointB,m_pointC,m_pointD),L"DEGENERATE TETRAHEDRON ERROR: Attempting to create a tetrahedron with four coplanar points (they lie on the same plane).");
}

void Tetrahedron::Create(Point A, Point B,Point C, Point D)
{
	m_pointA = A;
	m_pointB = B;
	m_pointC = C;
	m_pointD = D;
	
	Assert(AreInequal(m_pointA,m_pointB,m_pointC,m_pointD),L"DEGENERATE TETRAHEDRON ERROR: Attempting to create a tetrahedron with four non-unique points (points are equal to another)");
	Assert(AreNotCollinear(m_pointA,m_pointB,m_pointC,m_pointD),L"DEGENERATE TETRAHEDRON ERROR: Attempting to create a tetrahedron with three collinear points (they lie on the same line).");
	Assert(AreNotCoplanar(m_pointA,m_pointB,m_pointC,m_pointD),L"DEGENERATE TETRAHEDRON ERROR: Attempting to create a tetrahedron with four coplanar points (they lie on the same plane).");
}

Point Tetrahedron::ClosestPoint(const Point& A, const Point& B,const Point& C,const Point& D, const Point& O)
{
	Assert(AreInequal(A,B,C,D),L"DEGENERATE TETRAHEDRON ERROR: The tetrahedron has four non-unique points (points are equal to another)");
	Assert(AreNotCollinear(A,B,C,D),L"DEGENERATE TETRAHEDRON ERROR: The tetrahedron has three collinear points (they lie on the same line).");
	Assert(AreNotCoplanar(A,B,C,D),L"DEGENERATE TETRAHEDRON ERROR: The tetrahedron has four coplanar points (they lie on the same plane).");


}

Distance Tetrahedron::DistanceToPoint(const Point& A, const Point& B,const Point& C,const Point& D, const Point& O)
{
	return sqrt(Distance2ToPoint(A,B,C,D,O));
}

Distance2 Tetrahedron::Distance2ToPoint(const Point& A, const Point& B,const Point& C,const Point& D, const Point& O)
{
	return (mLength2(O - ClosestPoint(A,B,C,D,O)));
}

bool Tetrahedron::Contains(const Point& A, const Point& B,const Point& C, const Point& D,const Point& O)
{
	return Distance2ToPoint(A,B,C,D,O) == 0;
}


//QuadPlanes& Tetrahedron::GetPlanes(QuadPlanes& planes) const
//{
//	planes.planes[0] = Plane(m_pointA,m_pointB,m_pointC);
//	if (!planes.planes[0].GetHalfspace(m_pointD)) 
//		planes.planes[0].Invert();
//
//	planes.planes[1] = Plane(m_pointA,m_pointB,m_pointD);
//	if (!planes.planes[1].GetHalfspace(m_pointC)) 
//		planes.planes[1].Invert();
//
//	planes.planes[2] = Plane(m_pointA,m_pointC,m_pointD);
//	if (!planes.planes[2].GetHalfspace(m_pointB)) 
//		planes.planes[2].Invert();
//
//	planes.planes[3] = Plane(m_pointB,m_pointC,m_pointD);
//	if (!planes.planes[3].GetHalfspace(m_pointA)) 
//		planes.planes[3].Invert();
//
//	return planes;
//}