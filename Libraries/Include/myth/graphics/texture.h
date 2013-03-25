
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
		//! The texture object representing a 2D image [Texture2D]
		struct declspec_graphics Texture
		{
		public:
			//! Empty constructor
			Texture();
			//! Initialization constructor, loads a texture from a specified file
			Texture(GLenum textureType, const char* filename);
			//! Initialization constructor, creates a 2D texture with the specified with and height and the specified format
			Texture(int width, int height, GLenum format);
			//! Destructor
			~Texture();

			bool Load();
			void Unload();

			GLuint id(){return m_texture;}

			//! Binds the texture to the specified texture slot, a simple enum that indicates which texture # it is, starting at GL_TEXTURE0 
			void Bind(int index) const;
		private:
			const char* m_filename;

			GLenum m_textureType;
			GLuint m_texture;
		};
	}
}