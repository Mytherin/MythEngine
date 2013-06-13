
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
		enum {
			FRAMEBUFFER_DEPTH = 0x01,
			FRAMEBUFFER_STENCIL = 0x02,
			FRAMEBUFFER_COLOR = 0x04
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

			void Destroy();

			//! Initializes the frame buffer with the given width and height values
			void Init(unsigned int width, unsigned int height);

			GLuint GetTexture() { return m_texture;}
			GLuint GetDepth() { return m_depth;}
			GLuint GetStencil() { return m_stencil;}

			void AttachTexture(GLenum attachmentPoint, GLuint texture);
			void AttachRenderbuffer(GLenum attachmentPoint, GLuint renderbuffer);
			
			//! Binds the framebuffer for writing; any meshes rendered after this point will be rendered to the framebuffer
			void Bind();
			void Unbind();
		private:
			//! The type of the frame buffer that defines which type of information is stored, this can be: GL_DEPTH_ATTACHMENT, GL_COLOR_ATTACHMENT, GL_STENCIL_ATTACHMENT, GL_DEPTH_STENCIL_ATTACHMENT
			GLenum m_type;

			bool m_depthTexture;
			bool m_stencilTexture;

			GLuint m_depth;
			GLuint m_stencil;
			GLuint m_texture;

			GLuint m_framebuffer;
		};
	}
}