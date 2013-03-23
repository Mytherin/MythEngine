
#include <myth\debug\assert.h>
#include <myth\graphics\texture.h>
#include <SOIL.h>

using namespace myth::graphics;

Texture::Texture() : 
	m_texture(0),m_filename(0)
{
}

Texture::Texture(GLenum textureType, const char* filename) :
	m_textureType(textureType), m_filename(filename)
{
}

Texture::Texture(int width, int height, GLenum format) : 
	m_textureType(GL_TEXTURE_2D),m_filename(0)
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

bool Texture::Load()
{
	Assert(m_filename,"TEXTURE LOAD ERROR: Attempting to load a texture from a file without specifying a file address");

	glGenTextures(1,&m_texture);
	m_texture = SOIL_load_OGL_texture(m_filename,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);

	DEBUGIF(m_texture == 0)
	{
		printf("TEXTURE LOAD ERROR: Failure to load texture \"%s\". Does the file with the specified filename exist and is it one of the supported formats by SOIL?\n",m_filename);

		Assert(0,"TEXTURE LOADING ERROR: Failure to load texture.");
	}
	
	return m_texture != 0;
}

void Texture::Unload()
{
}

void Texture::Bind(int index) const
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(m_textureType,m_texture);
}
