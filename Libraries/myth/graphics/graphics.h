
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif


#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

namespace myth
{
	namespace graphics
	{
		class declspec_graphics Graphics
		{
		public:
			Graphics(){}
			virtual ~Graphics(){}
			

			//! Virtual function called when the graphics context is created
			virtual void Create();
			//! Virtual function called to destroy the graphics context
			virtual void Destroy() = 0;
			//! Swaps the buffers of the device context, drawing the new buffer to the screen
			virtual void SwapBuffer() = 0;
		};

	}
}