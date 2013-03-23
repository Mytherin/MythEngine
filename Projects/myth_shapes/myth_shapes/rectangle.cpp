
#include <myth\debug\assert.h>
#include <myth\debug\assertfunctions.h>
#include <myth\phys\rectangle.h>

using myth::phys::Distance;
using myth::phys::Distance2;
using myth::phys::Point;
using myth::phys::Rectangle;


Rectangle::Rectangle(Point A, Point B, Point C):
	m_pointA(A),m_pointB(B),m_pointC(C)
{
	Assert(AreInequal(m_pointA,m_pointB,m_pointC),L"DEGENERATE TRIANGLE ERROR: Attempting to create a rectangle with three non-unique points (points are equal to eachother).");
	Assert(AreNotCollinear(m_pointA,m_pointB,m_pointC),L"DEGENERATE TRIANGLE ERROR: Attempting to create a rectangle with three collinear vertices (they lie on the same line).");
}

Point Rectangle::ClosestPoint(const Point& A, const Point& B,const Point& C, const Point& O)
{
	Offset ab(B - A);              //get the two direction vectors that define the rectangle (A => B and A => C)
	Offset ac(C - A);
	Offset d(O - A); 	           //transform the point to the rectangle's coordinate system by subtracting them from A

	Point closestPoint(A);         //we start our point at the origin of our coordinate system, which is point A as we have transformed all our points

	float dist(mDot(d,ab));         //project the projected point along the line A => B and see how far along this line it is
	float maxdist(mDot(ab,ab));     //the distance must be clamped to the rectangle, it cannot be before A or past B on the A => B line segment
	if (dist >= maxdist)       
		closestPoint += ab;        //if the point lies past B, we clamp it to B
	else if (dist > 0.0f)
		closestPoint += (dist / maxdist) * ab; //otherwise if it lies between A and B, we move it along the proper distance

	dist = mDot(d,ac);              //repeat the process for the A => C
	maxdist = mDot(ac,ac);
	if (dist >= maxdist)
		closestPoint += ac;
	else if (dist > 0)
		closestPoint += (dist / maxdist) * ac;

	//we have now obtained the barycentric coordinates of the point and clamped them to the rectangle, this is the closest point

	return closestPoint;
}

Distance Rectangle::DistanceToPoint(const Point& A, const Point& B,const Point& C, const Point& O)
{
	return sqrt(Distance2ToPoint(A,B,C,O));
}

Distance2 Rectangle::Distance2ToPoint(const Point& A, const Point& B,const Point& C, const Point& O)
{
	return (mLength2(O - ClosestPoint(A,B,C,O)));
}

bool Rectangle::Contains(const Point& A, const Point& B,const Point& C, const Point& O)
{
	return Distance2ToPoint(A,B,C,O) == 0;
}