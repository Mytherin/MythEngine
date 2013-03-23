
#include <myth\debug\assert.h>
#include <myth\debug\assertfunctions.h>
#include <myth\phys\triangle.h>
#include <gtx\norm.hpp>

using myth::phys::Distance;
using myth::phys::Distance2;
using myth::phys::Normal;
using myth::phys::Offset;
using myth::phys::Point;
using myth::phys::Triangle;

Triangle::Triangle(Point pointA, Point pointB, Point pointC)
	: m_pointA(pointA),m_pointB(pointB),m_pointC(pointC)
{
	Assert(AreInequal(m_pointA,m_pointB,m_pointC),L"DEGENERATE TRIANGLE ERROR: Attempting to create a triangle with three non-unique points (points are equal to eachother).");
	Assert(AreNotCollinear(m_pointA,m_pointB,m_pointC),L"DEGENERATE TRIANGLE ERROR: Attempting to create a triangle with three collinear vertices (they lie on the same line).");
}

void Triangle::Create(Point pointA, Point pointB, Point pointC)
{
	m_pointA = pointA;
	m_pointB = pointB;
	m_pointC = pointC;

	Assert(AreInequal(m_pointA,m_pointB,m_pointC),L"DEGENERATE TRIANGLE ERROR: Two of the points on the triangle are the same, has the triangle been initialized?");
	Assert(AreNotCollinear(m_pointA,m_pointB,m_pointC),L"DEGENERATE TRIANGLE ERROR: The three vertices are collinear, the triangles vertices lie on the same line.");
}



Point Triangle::ClosestPoint(const Point& A, const Point& B,const Point& C, const Point& O)
{
	Offset ab(B - A);            // A => B  
	Offset ac(C - A);            // A => C
	
	//check if the point lies inside the voronai region of vertex A
	Offset ao(O - A); 	         // A => O
	float d1 = mDot(ab,ao);        //project the point onto A => B
	float d2 = mDot(ac,ao);        //project the point onto A => C

	if (d1 <= 0.0f && d2 <= 0.0f) return A; //it lies in the vertex region, return the vertex

	//check if the point lies inside the voronai region of vertex B
	Offset bo(O - B);
	float d3 = mDot(ab,bo);
	float d4 = mDot(ac,bo);

	if (d3 >= 0.0f && d4 <= d3) return B; //it lies in the vertex region, return the vertex

	//check if the point lies inside the voronai region of edge AB
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3); //it lies in the edge region, project the point onto the edge
		return A + v * ab;
	}

	//check if the point lies inside the voronai region of vertex C
	Offset co(O - C);
	float d5 = mDot(ab,co);
	float d6 = mDot(ac,co);

	if (d6 >= 0.0f && d5 <= d6) return C; //it lies in the vertex region, return the vertex

	//check if the point lies inside the voronai region of edge AC
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6); //it lies in the edge region, project the point onto the edge
		return A + w * ac;
	}

	//check if the point lies inside the voronai region of edge BC
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float u = (d4 - d3) / ((d4 - d3) + (d5 - d6)); //it lies in the edge region, project the point onto the edge
		return B + u * (C - B);
	}

	//the point lies inside the face region, compute the barycentric coordinates of the point within the triangle
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;

	return A + ab * v + ac * w;

}

Distance Triangle::DistanceToPoint(const Point& A, const Point& B,const Point& C, const Point& O)
{
	return sqrt(Distance2ToPoint(A,B,C,O));
}

Distance2 Triangle::Distance2ToPoint(const Point& A, const Point& B,const Point& C, const Point& O)
{
	return (mLength2(O - ClosestPoint(A,B,C,O)));
}

bool Triangle::Contains(const Point& A, const Point& B,const Point& C, const Point& O)
{
	return Distance2ToPoint(A,B,C,O) == 0;
}