
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

Texture::Texture(int width, int height, GLenum format) : 
	FileAsset(0,0),m_textureType(GL_TEXTURE_2D),m_texture(0)
{
	glGenTextures(1,&m_texture); //generate a texture

	glBindTexture(GL_TEXTURE_2D,m_texture); //bind

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_FLOAT, NULL); //set the data that will be stored within this texture

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //set the interpolation method used for the texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //clamp any values written into the texture to the edge
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D,0); //unbind
}

Texture::~Texture()
{
}


void Texture::LoadFromFile(std::string filepath)
{
	glGenTextures(1,&m_texture);
	m_texture = SOIL_load_OGL_texture(filepath.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);

	DEBUGIF(m_texture == 0)
	{
		printf("TEXTURE LOAD ERROR: Failure to load texture \"%s\". Does the file with the specified filename exist and is it one of the supported formats by SOIL?\n",filepath);

		Assert(0,"TEXTURE LOADING ERROR: Failure to load texture.");
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
