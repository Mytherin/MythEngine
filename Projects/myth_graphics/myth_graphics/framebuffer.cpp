

#include <myth\debug\assert.h>
#include <cstdio>
#include <myth\graphics\framebuffer.h>

using namespace myth::graphics;

Framebuffer::Framebuffer() : m_type(0)
{
}

Framebuffer::Framebuffer(GLenum type) : m_type(type)
{

}

Framebuffer::~Framebuffer()
{
	if (m_framebuffer > 0) glDeleteFramebuffers(1,&m_framebuffer);
}

void Framebuffer::Init(unsigned int width, unsigned int height)
{
	Assert(m_type,"FRAME BUFFER ERROR: The frame buffer was not properly initialized prior to calling one of its functions.");


	//create a render buffer to store depth value
	//glGenRenderbuffersEXT(1,&m_depth); //generate the depth render buffer

	//glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,m_depth); //bind it so we can initialize it

	//glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,GL_DEPTH_COMPONENT,width,height); //set its storage type to hold depth information
	//glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,GL_DEPTH_ATTACHMENT_EXT,GL_RENDERBUFFER_EXT,m_depth); //

	//glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,0); //unbind the renderbuffer


	//create a texture to store depth value
	//glGenTextures(1,&m_depth); //generate a texture

	//glBindTexture(GL_TEXTURE_2D,m_depth); //bind

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); //set the data that will be stored within this texture

	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //set the interpolation method used for the texture
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //clamp any values written into the texture to the edge
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//create a texture to store color value
	//glBindTexture(GL_TEXTURE_2D,0); //unbind

	//glGenTextures(1,&m_texture); //generate a texture

	//glBindTexture(GL_TEXTURE_2D,m_texture); //bind

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL); //set the data that will be stored within this texture

	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //set the interpolation method used for the texture
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //clamp any values written into the texture to the edge
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//glBindTexture(GL_TEXTURE_2D,0); //unbind

	m_framebuffer = 0;

	m_depth = Texture(width,height,GL_DEPTH_COMPONENT);
	m_texture = Texture(width,height,GL_RGBA);

	//set up the frame buffer
	glGenFramebuffers(1,&m_framebuffer); 

	glBindFramebuffer(GL_FRAMEBUFFER,m_framebuffer); //bind

	//glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,GL_DEPTH_ATTACHMENT_EXT,GL_RENDERBUFFER_EXT,m_depth.);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  m_depth.id(),0); 
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,  m_texture.id(),0); 

	
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("FRAMEBUFFER ERROR: %s\n", gluErrorString(glGetError()));
		Assert(0,"FRAMEBUFFER ERROR: Did not successfully create the framebuffer.");
	}

	glBindFramebuffer(GL_FRAMEBUFFER,0); //unbind
}

void Framebuffer::StartWrite()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
}

void Framebuffer::EndWrite()
{
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}