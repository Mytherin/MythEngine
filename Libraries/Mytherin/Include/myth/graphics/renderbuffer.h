
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
		//! The texture object representing an OpenGL renderbuffer object
		class declspec_graphics Renderbuffer
		{
		public:
			static GLuint GenerateRenderbuffer(unsigned int width, unsigned int height, GLenum dataType);
		};
	}
}