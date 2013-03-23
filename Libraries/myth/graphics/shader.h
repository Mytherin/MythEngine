
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <myth\resources\asset.h>

namespace myth
{
	namespace graphics
	{
		class ShaderProgram;

		//! The shader object represents a GLSL shader program
		class declspec_graphics Shader : public myth::resources::Asset
		{
		public:
			Shader(GLenum shaderType,myth::resources::AssetData *assetData, int package);
			virtual ~Shader();

			void Load(std::string source);
			void Reload(std::string source);
			void Destroy();
			bool IsLoaded();

			void Attach();

			GLuint id() const{return m_shaderHandle;}
			GLenum type() const{return m_shaderType;}
		private:
			static GLuint Create(GLenum type, std::string source);

			GLuint m_shaderHandle;
			GLenum m_shaderType;
		};

		class VertexShader : public Shader
		{
		public:
			VertexShader(myth::resources::AssetData *assetData, int package) : Shader(GL_VERTEX_SHADER,assetData,package){}
			~VertexShader();
		};

		class FragmentShader : public Shader
		{
		public:
			FragmentShader(myth::resources::AssetData *assetData, int package) : Shader(GL_FRAGMENT_SHADER,assetData,package){}
			~FragmentShader();
		};
	}
}