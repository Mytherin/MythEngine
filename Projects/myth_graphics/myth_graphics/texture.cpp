
#include <myth\debug\assert.h>
#include <myth\graphics\texture.h>
#include <cstdio>
#include <SOIL.h>

using namespace myth::graphics;

Texture::Texture() : 
	FileAsset(0,0),m_textureType(GL_TEXTURE_2D),m_texture(0)
{

}

Texture::Texture(GLenum textureType, myth::assets::FilePath *assetData, int package) :
	FileAsset(assetData,package),m_textureType(textureType)
{
}

Texture::~Texture()
{
}


void Texture::LoadFromFile(std::string filepath)
{
	switch(m_textureType)
	{
		case GL_TEXTURE_2D:
			m_texture = SOIL_load_OGL_texture(filepath.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);

			DEBUGIF(m_texture == 0)
			{
				printf("TEXTURE LOAD ERROR: Failure to load texture \"%s\". Does the file with the specified filename exist and is it one of the supported formats by SOIL?\n",filepath);

				Assert(0,"TEXTURE LOADING ERROR: Failure to load texture.");
			}
			return;
		case GL_TEXTURE_3D:
			m_texture = SOIL_load_OGL_single_cubemap(
					filepath.c_str(),
					"UWSEND",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS |  SOIL_FLAG_DDS_LOAD_DIRECT
				);
			
			DEBUGIF(m_texture == 0)
			{
				printf("TEXTURE LOAD ERROR: Failure to load texture \"%s\". Does the file with the specified filename exist and is it one of the supported formats by SOIL?\n",filepath);

				Assert(0,"TEXTURE LOADING ERROR: Failure to load texture.");
			}
			return;
		default:
			Assert(false,"TEXTURE LOAD ERROR: Invalid texture type specified.");
	}

}

void Texture::ReloadFromFile(std::string filepath)
{
	Destroy();
	LoadFromFile(filepath);
}

void Texture::Destroy()
{
	m_texture = 0;
}

bool Texture::IsLoaded()
{
	return m_texture;
}

void Texture::Bind(int index) const
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(m_textureType,m_texture);
}

GLuint Texture2D::GenerateTexture(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum storageType, GLenum textureOptions)
{
	GLuint texture(0);
	glGenTextures(1,&texture); //generate a texture

	glBindTexture(GL_TEXTURE_2D,texture); //bind

	if (textureOptions & TEXTURE_WRAP_REPEAT)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	if (textureOptions & TEXTURE_MINMAG_NEAREST)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	if (textureOptions & TEXTURE_DEPTH_INTENSITY)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	}
	if (textureOptions & TEXTURE_COMPAREMODE_RTOTEXTURE)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	}
	if (textureOptions & TEXTURE_COMPAREFUNC_LEQUAL)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, storageType, NULL); //set the data that will be stored within this texture
	
	glBindTexture(GL_TEXTURE_2D,0); //unbind

	return texture;
}