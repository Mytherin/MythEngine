
#include <myth\debug\assert.h>
#include <myth\phys\ray.h>
#include <gtx\norm.hpp>

using myth::phys::Distance;
using myth::phys::Distance2;
using myth::phys::Point;
using myth::phys::Ray;

Ray::Ray(Point startPoint, Point otherPoint) : m_startPoint(startPoint),m_endPoint(otherPoint)
{
	Assert(m_startPoint != m_endPoint,L"DEGENERATE RAY ERROR: The start and end points of the ray are the same. Has the line been initialized?");
}


Point Ray::ClosestPoint(const Point& a, const Point& b, const Point& c)
{
	Assert(a != b,L"DEGENERATE RAY ERROR: The start and end points of the ray are the same. Has the ray been initialized?");
	Offset line = b - a;

	float t = mDot(line,c-a) / mLength2(line);

	if (t <= 0) return a;

	return a + line * t;
}

Distance Ray::DistanceToPoint(const Point& a, const Point& b, const Point& c)
{
	return sqrt(Distance2ToPoint(a,b,c));
}

Distance2 Ray::Distance2ToPoint(const Point& a, const Point& b, const Point& c)
{
	Assert(a != b,L"DEGENERATE RAY ERROR: The start and end points of the ray are the same. Has the ray been initialized?");
	Offset ab = b - a;
	Offset ac = c - a;

	float e = mDot(ac,ab);
	if (e <= 0.0f) return mDot(ac,ac);

	return mDot(ac,ac) - e * e / mDot(ab,ab);
}

bool Ray::Contains(const Point& a, const Point& b, const Point& c)
{
	return Distance2ToPoint(a,b,c) == 0;
}