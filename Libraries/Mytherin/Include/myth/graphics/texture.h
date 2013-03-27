
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
		//! The texture object representing a 2D image [Texture2D]
		class declspec_graphics Texture : public myth::assets::FileAsset
		{
		public:
			//! Empty Constructor
			Texture();
			//! Initialization constructor
			Texture(GLenum textureType, myth::assets::FilePath *assetData, int package);
			//! Initialization constructor, creates a 2D texture with the specified width and height and the specified format
			Texture(int width, int height, GLenum format);
			//! Destructor
			~Texture();

			virtual void LoadFromFile(std::string filepath);
			virtual void ReloadFromFile(std::string filepath);
			virtual void Destroy();
			virtual bool IsLoaded();

			GLuint id(){return m_texture;}

			//! Binds the texture to the specified texture slot, a simple enum that indicates which texture # it is, starting at GL_TEXTURE0 
			void Bind(int index) const;
		private:
			GLenum m_textureType;
			GLuint m_texture;
		};

		class Texture2D : public Texture
		{
		public:
			Texture2D(myth::assets::FilePath *assetData, int package) : Texture(GL_TEXTURE_2D,assetData,package){}
			~Texture2D(){}
		};
		
		class Texture3D : public Texture
		{
		public:
			Texture3D(myth::assets::FilePath *assetData, int package) : Texture(GL_TEXTURE_3D,assetData,package){}
			~Texture3D(){}
		};
	}
}