
#pragma once

namespace myth
{
	namespace math
	{
		const float pi = 3.141592653589f;

		inline int clamp(const int val, const int min, const int max)
		{
			return (val < min) ? min : (val > max ? max : val);
		}
		
		inline float clamp(const float val, const float min, const float max)
		{
			return (val < min) ? min : (val > max ? max : val);
		}

		inline double clamp(const double val, const double min, const double max)
		{
			return (val < min) ? min : (val > max ? max : val);
		}
	}
}