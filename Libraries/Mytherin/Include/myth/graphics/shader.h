
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <myth\assets\asset.h>

namespace myth
{
	namespace graphics
	{
		class ShaderProgram;

		const int DefaultDirectionalLights = 8;
		const int DefaultPointLights = 8;
		const int DefaultSpotLights = 8;
		const int DefaultSampler2DCount = 4;
		const int DefaultSampler3DCount = 4;

		//! The shader object represents a GLSL shader program
		class declspec_graphics Shader : public myth::assets::SourceAsset
		{
		public:
			Shader(GLenum shaderType,myth::assets::AssetData *assetData, int package);
			virtual ~Shader();
			
			virtual void LoadFromSource(std::string source);
			virtual void ReloadFromSource(std::string source);
			virtual void Destroy();
			virtual bool IsLoaded();

			void Attach();

			GLuint id() const{return m_shaderHandle;}
			GLenum type() const{return m_shaderType;}

			int MaxDirectionalLights() { return m_maxdirectionalLights;}
			int MaxPointLights() { return m_maxpointLights;}
			int MaxSpotLights() { return m_maxspotLights;}
			int MaxSampler2DCount() { return m_sampler2DCount;}
			int MaxSampler3DCount() { return m_sampler3DCount;}
		private:
			GLuint Create(GLenum type, std::string source);

			int m_maxdirectionalLights;
			int m_maxpointLights;
			int m_maxspotLights;
			int m_sampler2DCount;
			int m_sampler3DCount;

			GLuint m_shaderHandle;
			GLenum m_shaderType;
		};

		class VertexShader : public Shader
		{
		public:
			VertexShader(myth::assets::AssetData *assetData, int package) : Shader(GL_VERTEX_SHADER,assetData,package){}
			~VertexShader(){}
		};

		class FragmentShader : public Shader
		{
		public:
			FragmentShader(myth::assets::AssetData *assetData, int package) : Shader(GL_FRAGMENT_SHADER,assetData,package){}
			~FragmentShader(){}
		};
	}
}