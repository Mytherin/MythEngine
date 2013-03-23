
#pragma once

#include <myth\phys\shapes.h>
#include <myth\math\math.h>

//! Global Namespace
/*!
This namespace contains all of the components of the Mytherin engine library. 
*/
namespace myth
{
	//! Physics
	/*!
	The namespace contains the components used by the physics engine of the Mytherin engine library
	*/
	namespace phys
	{
		//! [Interface] A base class for types of bounding volumes
		/*!
		The IBoundingVolume is a pure virtual base class that is used to implement bounding volumes that represent certain area's. 
		It implements a set of virtual methods dealing with collision detection between bounding volumes.
		*/
		class __declspec(dllexport) IBoundingVolume
		{
		public:
			IBoundingVolume(shape_type type) : m_type(type){};

			virtual ~IBoundingVolume() {}

			//! Collision test with another bounding volume.
			/*! 
			Performs a simply collision test between this bounding volume and another bounding volume
			\param other the bounding volume to test collision with
			\return Whether or not the two bounding volumes intersect.
			*/
			virtual bool Intersects(const AABB& other) const = 0;
			virtual bool Intersects(const Point& other) const = 0;
			virtual bool Intersects(const Ray& other) const = 0;
			virtual bool Intersects(const Sphere& other) const = 0;

			shape_type ShapeType(){return m_type;}
		protected:
			shape_type m_type;
		};
	}
}