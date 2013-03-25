
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <glm.hpp>

#include <myth\graphics\camera.h>
#include <myth\graphics\shaderconstants.h>
#include <myth\graphics\material.h>
#include <myth\graphics\shader.h>
#include <myth\graphics\vertex.h>
#include <myth\assets\asset.h>
#include <myth\assets\resourcelinks.h>

namespace myth
{
	namespace graphics
	{
		//! A shader program represents a collection of shaders used by OpenGL
		/*! A shaderprogram can include one of every type of OpenGL shaders: 
		GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER

		Shaders have the following rules:
		The attribute "Position" refers to the vertex position as vec3
		The attribute "Normal" refers to the vertex normal as vec3
		The attribute "TexCoord" refers to the texture coordinate of the vertex as vec2
		*/
		class declspec_graphics ShaderProgram : public myth::assets::Asset
		{
		public:
			//! Empty Constructor
			ShaderProgram(myth::assets::AssetData *assetData, int package);
			//! Destructor
			~ShaderProgram();

			virtual void LoadFromSource(std::string source);
			virtual void ReloadFromSource(std::string source);
			virtual void Destroy();
			virtual bool IsLoaded();

			//! Activate the shader program, binding it to OpenGL so it will be used for rendering. 
			/*!The shader program must be linked before being activated, this is done through the "Link()" function
			*/
			void Activate() const;

			static void Deactivate();

			void AttachShader(Shader& shader);
			void RemoveShader(Shader& shaderType);

			//! Links the shader program with OpenGL, allowing it to be used
			void Link();
			//! Validates whether or not the shader was successfully linked and is ready for use
			bool Validate();

			//! Binds an attribute to a specific index
			void BindAttribLocation(GLuint location, const char * name);
			void BindFragDataLocation(GLuint location, const char * name );

			//! Gets the index of a uniform variable of the specified name, returns -1 if the uniform variable does not exist
			int GetUniformLocation(const char *name) const;
			//! Gets the index of a uniform variable of the specified name inside an array, returns -1 if the uniform variable does not exist
			/*!
			\param name The name of the uniform variable to find the location of, the name should contain "%i" at the location of the array index, (e.g. "Array[%i].Attribute"), the array index is then provided as a second variable 
			\param str A character array that is used as a temporary container to write the uniform name (with the substituted array index), this should be big enough to fit the entire uniform name within it
			\param arrayloc The array index of the uniform variable
			*/
			int GetUniformLocation(const char *start, const char *end, int index, std::stringstream& ss) const;
			//! Returns whether or not a uniform variable with the specified name exists
			bool UniformExists(const char *name) const;

			void SetUniform(GLuint uniformLocation,float x, float y, float z) { SetUniform(uniformLocation,glm::vec3(x,y,z)); }
			void SetUniform(GLuint uniformLocation, const Vector2 & v) { glUniform2fv(uniformLocation,1,&v[0]);}
			void SetUniform(GLuint uniformLocation, const Vector3 & v) { glUniform3fv(uniformLocation,1,&v[0]);}
			void SetUniform(GLuint uniformLocation, const Vector4 & v) { glUniform4fv(uniformLocation,1,&v[0]);}
			void SetUniform(GLuint uniformLocation, const glm::mat3 & m)  { glUniformMatrix3fv(uniformLocation,1,GL_FALSE,&m[0][0]);}
			void SetUniform(GLuint uniformLocation, const glm::mat4 & m) { glUniformMatrix4fv(uniformLocation,1,GL_FALSE,&m[0][0]);}
			void SetUniform(GLuint uniformLocation, double val) { glUniform1dv(uniformLocation,1,&val);}
			void SetUniform(GLuint uniformLocation, float val) { glUniform1fv(uniformLocation,1,&val);}
			void SetUniform(GLuint uniformLocation, int val) { glUniform1iv(uniformLocation,1,&val);}
			void SetUniform(GLuint uniformLocation, bool val) { glUniform1i(uniformLocation,val);}

			template <class T>
			void NSetUniform(const char *name, const T& val) 
			{ 
				SetUniform(GetUniformLocation(name),val);
			}

			//! Prints all attributes within this shader to the console window
			void PrintAttributes() const;
			//! Prints all uniform variables within this shader to the console window
			void PrintUniforms() const;
			//! Prints all uniform variables and their values within this shader to the console window
			void PrintUniformValues() const;
			
			//!
			void BindCamera(const Camera& camera);
			//!
			void BindModel(const glm::mat4 model);
			//!
			void BindMaterial(const Material& material);
			//!
			void BindLights();
			//!
			void BindTexture(GLuint texture, int index);

			//! Gets the index of the specified shader type, ranging from 0..4
			int GetShaderIndex(GLenum shaderType) const;

			UniformLocations Uniforms;
		private:
			bool m_linked;

			myth::assets::ResourceLinks<Shader> m_shaders;

			GLuint m_shaderProgram;

			const Camera *m_linkedCamera;

			void GenerateUniformLocations();
		};
	}
}