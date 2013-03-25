

#pragma once

#include <myth\phys\iboundingvolume.h>
#include <vector>

namespace myth
{
	namespace phys
	{
		typedef std::vector<Point> Points;

		struct Extremes
		{
			Point *xmin;
			Point *xmax;
			Point *ymin;
			Point *ymax;
			Point *zmin;
			Point *zmax;
		};

		//! [Bounding Volume] Point Cloud
		/*!
		A point cloud is simply an unordered set of points
		*/
		class __declspec(dllexport) PointCloud
		{
		public:
			//! Empty Constructor
			PointCloud() : m_points(0) {}
			//! Initialization Constructor
			PointCloud(const Points& points);
			//! Destructor
			~PointCloud(){}

			void Create(const Points& points);

			//! Add a point to the point cloud
			void Add(Point point);

			//! Returns whether or not a specific point exists within the point cloud
			/*!
			Loops through all vertices, O(n)
			*/
			bool Contains(const Point& point) const;
			//! Returns whether or not there are duplicate points within the point cloud
			/*!
			Loops through all loops vertices twice, O(n * n)
			*/
			bool ContainsDuplicates(const Points& points, float precision = 0.001) const;

			//! Computes the smallest bounding sphere containing all points of the point cloud
			/*!
			Uses the Welzl algorithm to compute the smallest bounding sphere of the point cloud, O(n) 
			*/
			Sphere BoundingSphere();
			//! Computes the smallest AABB containing all points of the point cloud
			/*!
			Uses ExtremeValues to get the extreme values of the point cloud, O(n)
			*/
			AABB BoundingAABB();
			//! Computes the smallest OBB containing all points of the point cloud
			OBB BoundingOBB(float precision = 0.02);
			//! Computes the convex hull of the point cloud, removing all vertices not part of the convex hull
			/*!
			Uses the quickhull algorithm, O(n log n)
			*/
			void ConvexHull();

			//! Finds the extreme points (points with the lowest x,y,z and the points with the highest x,y,z)
			/*!
			Loops through all the vertices in the point cloud; O(n)
			\param extremeValues The Extremes object to place the pointers to the extreme points in
			\return The input (extremeValues)
			*/
			Extremes& ExtremeValues(Extremes& extremeValues);

			//! Gets the amount of points in the point cloud
			size_t Count() const{return m_points.size();}

			Points m_points;
		};
	}
}