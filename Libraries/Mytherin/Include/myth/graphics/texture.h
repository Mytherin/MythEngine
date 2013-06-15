
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
		//! The texture object representing a texture
		class declspec_graphics Texture : public myth::assets::FileAsset
		{
		public:
			//! Empty Constructor, creates a GL_TEXTURE_2D object with no AssetData specified
			Texture();
			//! Initialization constructor
			Texture(GLenum textureType, myth::assets::FilePath *assetData, int package);
			//! Destructor
			~Texture();

			virtual void LoadFromFile(std::string filepath);
			virtual void ReloadFromFile(std::string filepath);
			virtual void Destroy();
			virtual bool IsLoaded();
			
			GLenum type() const{return m_textureType;}
			GLuint id() const{return m_texture;}

			//! Binds the texture to the specified texture slot, a simple enum that indicates which texture # it is, starting at GL_TEXTURE0 
			void Bind(int index) const;
		private:
			GLenum m_textureType;
			GLuint m_texture;
		};

		enum TextureOptions
		{
			TEXTURE_WRAP_REPEAT = 0x01,
			TEXTURE_MINMAG_NEAREST = 0x02,
			TEXTURE_DEPTH_INTENSITY = 0x04,
			TEXTURE_COMPAREMODE_RTOTEXTURE = 0x08,
			TEXTURE_COMPAREFUNC_LEQUAL = 0xF0
		};

		//! A 2D texture (image)
		class Texture2D : public Texture
		{
		public:
			Texture2D(myth::assets::FilePath *assetData, int package) : Texture(GL_TEXTURE_2D,assetData,package){}
			~Texture2D(){}

			//! Generates a 2D texture with a specified with and height using the specified data type (e.g. GL_RGBA)
			static GLuint GenerateTexture(unsigned int width, unsigned int height, GLenum internalFormat, GLenum dataType, GLenum storageType, GLenum textureOptions);
		};
		
		//! A 3D texture (cubemap)
		class Texture3D : public Texture
		{
		public:
			//! Initialization Constructor
			Texture3D(myth::assets::FilePath *assetData, int package) : Texture(GL_TEXTURE_3D,assetData,package){}
			//! Destructor
			~Texture3D(){}
		};
	}
}