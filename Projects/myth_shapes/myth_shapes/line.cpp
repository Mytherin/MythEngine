
#include <myth\debug\assert.h>
#include <myth\phys\line.h>

using myth::phys::Distance;
using myth::phys::Distance2;
using myth::phys::Line;
using myth::phys::Point;

Line::Line(Point startPoint, Point endPoint) 
	: m_startPoint(startPoint),m_endPoint(endPoint)
{
	Assert(m_startPoint != m_endPoint,L"DEGENERATE LINE ERROR: Attempting to create a line with identical start and end points.");
}

Point Line::ClosestPoint(const Point& a, const Point& b, const Point& c)
{
	Assert(a != b,L"DEGENERATE LINE ERROR: The start and end points of the line are the same. Has the line been initialized?");
	Offset line = b - a;

	float t = mDot(line,c-a) / mLength2(line);

	return a + line * t;
}

Distance Line::DistanceToPoint(const Point& a, const Point& b, const Point& c)
{
	return sqrt(Distance2ToPoint(a,b,c));
}

Distance2 Line::Distance2ToPoint(const Point& a, const Point& b, const Point& c)
{
	Assert(a != b,L"DEGENERATE LINE ERROR: The start and end points of the line are the same. Has the line been initialized?");
	Offset ab = b - a;
	Offset ac = c - a;

	float e = mDot(ac,ab);
	float f = mDot(ab,ab);

	return mDot(ac,ac) - e * e / f;
}

bool Line::Contains(const Point& a, const Point& b, const Point& c)
{
	return Distance2ToPoint(a,b,c) == 0;
}