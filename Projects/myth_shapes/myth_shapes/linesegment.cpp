
#include <myth\debug\assert.h>
#include <myth\phys\linesegment.h>

using myth::phys::Distance;
using myth::phys::Distance2;
using myth::phys::LineSegment;
using myth::phys::Point;

LineSegment::LineSegment(Point startPoint, Point endPoint) : m_startPoint(startPoint),m_endPoint(endPoint)
{
	Assert(m_startPoint != m_endPoint,L"DEGENERATE LINE SEGMENT ERROR: The start and end points of the line segment are the same. Has the line been initialized?");
}

Point LineSegment::ClosestPoint(const Point& a, const Point& b, const Point& c)
{
	Assert(a != b,L"DEGENERATE LINE SEGMENT ERROR: The start and end points of the line segment are the same. Has the line segment been initialized?");
	Offset line = b - a;

	float t = mDot(line,c-a) / mLength2(line);

	if (t < 0) return a;
	if (t > 1) return a + line;

	return a + line * t;
}

Distance LineSegment::DistanceToPoint(const Point& a, const Point& b, const Point& c)
{
	return sqrt(Distance2ToPoint(a,b,c));
}

Distance2 LineSegment::Distance2ToPoint(const Point& a, const Point& b, const Point& c)
{
	Assert(a != b,L"DEGENERATE LINE SEGMENT ERROR: The start and end points of the line segment are the same. Has the line segment been initialized?");
	Offset ab = b - a;
	Offset ac = c - a;

	float e = mDot(ac,ab);
	if (e <= 0.0f) return mDot(ac,ac);
	float f = mDot(ab,ab);
	if (e >= f) 
	{
		ab = c - b;
		return mDot(ab,ab);
	}

	return mDot(ac,ac) - e * e / f;
}

bool LineSegment::Contains(const Point& a, const Point& b, const Point& c)
{
	return Distance2ToPoint(a,b,c) == 0;
}


Point LineSegment::ClosestPointTemp(const Point& point) const
{
	Assert(m_startPoint != m_endPoint,L"DEGENERATE LINE SEGMENT ERROR: The start and end points of the line segment are the same. Has the line been initialized?");

	Offset line = m_endPoint - m_startPoint;
	float t = mDot(line,point-m_startPoint) / mLength2(line);

	if (t < 0) t = 0;
	else if (t > 1) t = 1;

	return m_startPoint + line * t;
}