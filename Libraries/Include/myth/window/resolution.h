
#pragma once


namespace myth
{
	namespace window
	{
		struct Resolution
		{
			Resolution(){}
			Resolution(int width, int height, int bpi, int frequency):
				width(width),height(height),bpi(bpi),frequency(frequency)
			{
			}

			//! Checks whether or not two resolutions are identical, no duplicate resolutions are stored in the list of available resolutions
			bool Equals(const Resolution& other)
			{
				return (other.width == width && other.height == height);
			}

			int frequency;
			int width;
			int height;
			int bpi;
		};
	}
}
