
#include <myth\debug\assert.h>
#include <myth\phys\aabb.h>
#include <myth\phys\line.h>
#include <myth\phys\obb.h>
#include <myth\phys\plane.h>
#include <myth\phys\pointcloud.h>
#include <myth\phys\sphere.h>
#include <myth\phys\tetrahedron.h>

using myth::phys::AABB;
using myth::phys::Line;
using myth::phys::PointCloud;
using myth::phys::OBB;
using myth::phys::Offset;
using myth::phys::Plane;
using myth::phys::Point;
using myth::phys::Points;
using myth::phys::Rotation;
using myth::phys::Sphere;
using myth::phys::Tetrahedron;

PointCloud::PointCloud(const Points& points) : m_points(points)
{
	Assert(!ContainsDuplicates(m_points),L"DEGENERATE POINT CLOUD ERROR: Attempting to create a point cloud with vertices that are not unique.");
}

void PointCloud::Create(const Points& points)
{
	m_points = points;
	Assert(!ContainsDuplicates(m_points),L"DEGENERATE POINT CLOUD ERROR: Attempting to create a point cloud with vertices that are not unique.");
}

//! Recursively computes the smallest sphere surrounding a set of points using Welzl's algorithm
Sphere SmallestSphere(Point *points[], unsigned int point, int support);

Sphere PointCloud::BoundingSphere()
{
	Assert(Count()>0,L"DEGENERATE POINT CLOUD ERROR: Cannot compute the bounding sphere for an empty point cloud.");
	Point **L = new Point*[Count()];

	for(unsigned int i = 0; i < Count(); ++i)
		L[i] = &m_points[i];

	Sphere sphere = SmallestSphere(L, Count(),0);

	delete[] L;

	return sphere;
}

AABB PointCloud::BoundingAABB()
{
	Assert(Count()>0,L"DEGENERATE POINT CLOUD ERROR: Cannot compute the bounding AABB for an empty point cloud.");
	Extremes extremes;
	ExtremeValues(extremes);
	return AABB(extremes.xmin->x, extremes.ymin->y, extremes.zmin->z, extremes.xmax->x, extremes.ymax->y, extremes.zmax->z);
}

void PointCloud::ConvexHull()
{
	Assert(Count()>=4,L"DEGENERATE POINT CLOUD ERROR: Cannot compute the convex hull for a point cloud with less than 4 points.");

	//copy an array of pointers to the points in the point cloud
	Point **L = new Point*[Count()];

	for(unsigned int i = 0; i < Count(); ++i)
		L[i] = &m_points[i];

	Point *A,*B,*C,*D;

	Extremes extremes;
	ExtremeValues(extremes);

	Assert(extremes.xmin != extremes.xmax,L"DEGENERATE POINT CLOUD ERROR: The point cloud only contains a single x-dimension.");
	Assert(extremes.ymin != extremes.ymax,L"DEGENERATE POINT CLOUD ERROR: The point cloud only contains a single y-dimension.");
	Assert(extremes.zmin != extremes.zmax,L"DEGENERATE POINT CLOUD ERROR: The point cloud only contains a single z-dimension.");

	A = extremes.xmin;
	B = extremes.xmax;
	//create a line between the minimum and maximum points, and find the point furthest away from this line
	//Line line(*A,*B);

	//int max;
	//float currentDist;

	//float maxDist(-1);
	//for(unsigned int i = 0; i < Count(); ++i)
	//{
	//	currentDist = line.DistanceFrom(m_points[i]);
	//	if (currentDist > maxDist)
	//	{
	//		max = i;
	//		maxDist = currentDist;
	//	}
	//}

	//Assert(maxDist > 0,L"DEGENERATE POINT CLOUD ERROR: All vertices on the point cloud are collinear. The point cloud is one-dimensional.");

	//C = max;
	////compute the plane from the three points we have found and find the point with the maximal distance from this plane
	//Plane plane(A,B,C);

	//maxDist = -1;
	//for(unsigned int i = 0; i < Count(); ++i)
	//{
	//	currentDist = plane.DistanceFrom(m_points[i]);
	//	if (currentDist > maxDist)
	//	{
	//		max = i;
	//		maxDist = currentDist;
	//	}
	//}

	//Assert(maxDist > 0,L"DEGENERATE POINT CLOUD ERROR: All vertices on the point cloud are coplanar. The point cloud is two-dimensional.");

	//D = max;
	////we now have a tetrahedron with four points that are guaranteed to be in the convex hull
	//Tetrahedron tetrahedron(*L[A],*L[B],*L[C],*L[D]);

	////now gather points outside of the tetrahedron; for each of the four planes of the tetrahedron we gather all points in the negative halfspace
	////these are guaranteed to lie outside of the tetrahedron
	//myth::phys::QuadPlanes planes;

	//tetrahedron.GetPlanes(planes);

	//std::vector<Point*> outsideSet[4];

	//for(unsigned int i = 0; i < 4; ++i)
	//{
	//	if (L[i] == 0) continue;

	//	if (!planes.planes[i].GetHalfspace(*L[i]))
	//	{
	//		outsideSet[i].push_back(L[i]);
	//		L[i] = 0;
	//	}
	//}

	////now we expand the tetrahedron to the points outside of the planes we have defined

	////notCompleted is true as long as there is a face that has vertices lying outside of it
	//bool notCompleted = true;
	//while(notCompleted)
	//{
	//	notCompleted = false;
	//	for(unsigned int i = 0; i < 4; ++i)
	//	{
	//		if (outsideSet[i].size() > 0) notCompleted = true;

	//		max = 0;
	//		maxDist = -1;
	//		//find the point in the set of outside points that is farthest away from the plane
	//		for(unsigned int j = 0; j < outsideSet[i].size(); ++j)
	//		{
	//			currentDist = planes.planes[i].DistanceFrom(*(outsideSet[i][j]));
	//			if (currentDist > maxDist)
	//			{
	//				max = j;
	//				maxDist = currentDist;
	//			}
	//		}


	//	}
	//}





	delete [] L;
}

myth::phys::Extremes& PointCloud::ExtremeValues(myth::phys::Extremes& values)
{
	values.xmin = &m_points[0];
	values.xmax = &m_points[0];
	values.ymin = &m_points[0];
	values.ymax = &m_points[0];
	values.zmin = &m_points[0];
	values.zmax = &m_points[0];
	for(unsigned int i = 1; i < Count(); ++i)
	{
		if (m_points[i].x < values.xmin->x) values.xmin = &m_points[i]; //min-x
		else if (m_points[i].x > values.xmax->x) values.xmax = &m_points[i]; //max-x

		if (m_points[i].y < values.ymin->y) values.ymin = &m_points[i]; //min-y
		else if (m_points[i].y > values.ymax->y) values.ymax = &m_points[i]; //max-y

		if (m_points[i].z < values.zmin->z) values.zmin = &m_points[i]; //min-z
		else if (m_points[i].z > values.zmax->z) values.zmax = &m_points[i]; //max-z
	}

	return values;
}



OBB PointCloud::BoundingOBB(float precision)
{
	return OBB();
}



Sphere SmallestSphere(Point *points[], unsigned int point, int support)
{
	Sphere sphere;
	//compute a sphere with the support points on its edge
	switch(support)
	{
	case 0:  sphere = Sphere(); break;
	case 1:  sphere = Sphere(*points[-1]); break;
	case 2:  sphere = Sphere(*points[-1],*points[-2]); break;
	case 3:  sphere = Sphere(*points[-1],*points[-2],*points[-3]); break;
	case 4:  return Sphere(*points[-1],*points[-2],*points[-3],*points[-4]);
	}

	Point* temp;
	Offset offset;
	for(unsigned int i = 0; i < point; ++i)
	{
		offset = sphere.m_center - *points[i];
		//test if the point is NOT within the sphere, if it is within the sphere already we do not need to add it to the sphere
		if(glm::dot(offset,offset) > sphere.m_radius * sphere.m_radius)
		{
			//if the new point lies outside of the sphere, we will expand the sphere with the new point
			//the smallest sphere containing both the current sphere and the new point has the new point lying on its edge, as well
			//as at least one point that lies on the edge of the current sphere

			for(unsigned int j = i; j > 0; --j)
			{
				temp = points[j];
				points[j] = points[j - 1];
				points[j - 1] = temp;
			}
			//recursively compute the smallest sphere with the new support points
			sphere = SmallestSphere(points+1, i, support + 1);
		}
	}
	return sphere;
}

void PointCloud::Add(Point point)
{
	Assert(!Contains(point),L"DEGENERATE POINT CLOUD ERROR: Attempting to add a point in the point cloud that is already present.");
	m_points.push_back(point);
}

bool PointCloud::ContainsDuplicates(const Points& points, float precision) const
{
	for(unsigned int i = 0; i < points.size(); ++i)
	{
		for(unsigned int j = i+1; j < points.size(); ++j)
		{
			if (points[i] == points[j])
			{
				return true;
			}
		}
	}
	return false;
}


bool PointCloud::Contains(const Point& point) const
{
	for(unsigned int i = 0; i < Count(); ++i)
		if (m_points[i].x == point.x && m_points[i].y == point.y && m_points[i].z == point.z)
			return true;
	return false;
}




//
//void RotatePoints(Points& points, Rotation rotation)
//{
//	glm::mat3 matrix = glm::mat3_cast(rotation);
//	for(unsigned int i = 0; i < points.size(); ++i)
//	{
//		points[i] = matrix * points[i];
//		int z = 5;
//	}
//}

//
//OBB PointCloud::BoundingOBB(float precision)
//{
//	Assert(Count()>0,L"DEGENERATE POINT CLOUD ERROR: Cannot compute the bounding OBB for an empty point cloud.");
//	ConvexHull();
//
//	Points tempPoints(m_points);
//
//	AABB startAABB = BoundingAABB();
//	float startVolume = startAABB.Volume();
//
//	AABB bestAABB;
//	AABB currentAABB;
//	int bestX, bestY, bestZ;
//	float bestVolume = FLT_MAX;
//
//	float pi = 3.14159265f;
//
//	Rotation xRotation, yRotation, zRotation;
//	xRotation.x += precision * pi;
//	yRotation.y += precision * pi;
//	zRotation.z += precision * pi;
//
//	for(int x = 0; x < 1/precision; ++x)
//	{
//		for(int y = 0; y < 1/precision; ++y)
//		{
//			for(int z = 0; z < 1/precision; ++z)
//			{
//				//currentAABB = BoundingAABB(tempPoints);
//				float volume = currentAABB.Volume();
//				if (volume < bestVolume)
//				{
//					bestAABB = currentAABB;
//					bestVolume = volume;
//					bestX = x, bestY = y, bestZ = z;
//				}
//				RotatePoints(tempPoints,zRotation);
//			}
//			RotatePoints(tempPoints,yRotation);
//		}
//		RotatePoints(tempPoints,xRotation);
//	}
//
//	return OBB();
//}