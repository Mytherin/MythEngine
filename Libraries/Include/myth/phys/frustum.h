
#pragma once

#include <myth\phys\iboundingvolume.h>
#include <myth\phys\plane.h>

namespace myth
{
	namespace phys
	{
		//! [Bounding Volume] Frustum
		class __declspec(dllexport) Frustum : public IBoundingVolume
		{
		public:
			//! Empty Constructor
			Frustum():IBoundingVolume(type_FRUSTUM) {} 
			//! Initialization Constructor
			Frustum(Plane far, Plane near, Plane left, Plane right, Plane top, Plane bottom) 
				: m_far(far),m_near(near),m_left(left),m_right(right),m_top(top),m_bottom(bottom),IBoundingVolume(type_FRUSTUM){}

			bool Intersects(const IBoundingVolume& other){return true;}

			Plane m_far, m_near, m_left, m_right, m_top, m_bottom;
		};
	}
}