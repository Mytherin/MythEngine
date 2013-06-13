
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
		class declspec_graphics ShadowMapFBO
		{
		public:
			ShadowMapFBO();

			~ShadowMapFBO();

			bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

			void BindForWriting();

			void BindForReading(GLenum TextureUnit){}

			int GetTexture() { return m_shadowMap;}

		private:
			GLuint m_fbo;
			GLuint m_shadowMap;
		};
	}
}