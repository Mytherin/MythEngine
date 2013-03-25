
#pragma once
#pragma warning(disable:4251)

#include <glm.hpp>
#include <gtx\norm.hpp>

//cast function names to clearer function names
#define mDot glm::dot
#define mLength glm::length
#define mLength2 glm::length2
#define mCross glm::cross
#define mNormalize glm::normalize

namespace myth
{
	namespace phys
	{
		//! Shape Type Enum
		/*!
		Contains an identifier for each different shape type a bounding volume can be
		*/
		enum {type_NULL = 0, type_AABB = 1, type_FRUSTUM = 2, type_SPHERE = 3, type_OBB = 4};

		//! The shape type of a bounding volume
		typedef unsigned char shape_type;

		class AABB;
		class Frustum;
		class Line;
		class LineSegment;
		class OBB;
		class Plane;
		class PointCloud;
		class Polyhedron;
		class Polygon;
		class Ray;
		class Rectangle;
		class Sphere;
		class Tetrahedron;
		class Triangle;


		//! Three Dimensional Direction (x,y,z)
		typedef glm::vec3 Direction;
		//! Three Dimensional Normal (x,y,z)
		typedef glm::vec3 Normal;
		//! Three Dimensional Point (x,y,z)
		typedef glm::vec3 Point;
		//! Two Dimensional Direction (x,y)
		typedef glm::vec2 Direction2D;
		//! Two Dimensional Point (x,y)
		typedef glm::vec2 Point2D;
		//! Two Dimensional Texture Coordinate (u,v)
		typedef glm::vec2 TexCoord;
		//! Three Dimensional Size (Width,Height,Depth)
		typedef glm::vec3 Size;
		//! Three Dimensional Offset (x,y,z)
		typedef glm::vec3 Offset;

		//! Volume of a bounding volume
		typedef float Volume;

		//! A distance measurement
		typedef float Distance;
		//! A squared distance measurement
		typedef float Distance2;

		//! Face of a three dimensional polyhedron
		typedef Triangle Face;
		//! Edge 
		typedef LineSegment Edge;

		inline Direction2D GetOrthogonal2D(Direction2D other)
		{
			return Direction2D(-other.y,other.x);
		}

		inline Direction GetOrthogonal3D(Direction other)
		{
			return Direction(other.y - other.z,other.z - other.x,other.x - other.y);
		}
	}
}