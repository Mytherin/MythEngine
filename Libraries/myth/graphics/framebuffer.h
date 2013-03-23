
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <myth\graphics\texture.h>

namespace myth
{
	namespace graphics
	{
		enum {
			FBTYPE_DEPTH = 0x01,
			FBTYPE_STENCIL = 0x02,
			FBTYPE_COLOR = 0x04
		} FramebufferType;


		class declspec_graphics Framebuffer
		{
		public:
			//! Empty constructor
			Framebuffer();
			//! Initialization constructor
			Framebuffer(GLenum type);
			//! Destructor
			~Framebuffer();

			//! Initializes the frame buffer with the given width and height values
			void Init(unsigned int width, unsigned int height);

			//! Binds the framebuffer for writing; any meshes rendered after this point will be rendered to the framebuffer
			void StartWrite();
			//!
			void EndWrite();

			Texture& GetTexture() { return m_texture;}
			Texture& GetDepth() { return m_depth;}
			Texture& GetStencil() { return m_stencil;}

		private:
			//! The type of the frame buffer that defines which type of information is stored, this can be: GL_DEPTH_ATTACHMENT, GL_COLOR_ATTACHMENT, GL_STENCIL_ATTACHMENT, GL_DEPTH_STENCIL_ATTACHMENT
			GLenum m_type;

			Texture m_depth;
			Texture m_stencil;
			Texture m_texture;

			GLuint m_framebuffer;
		};
	}
}