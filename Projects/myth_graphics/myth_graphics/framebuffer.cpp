

#include <myth\debug\assert.h>
#include <cstdio>
#include <myth\graphics\framebuffer.h>
#include <myth\graphics\renderbuffer.h>
#include <myth\graphics\texture.h>

using namespace myth::graphics;

Framebuffer::Framebuffer() : m_type(0), m_framebuffer(0),m_depth(0),m_texture(0),m_stencil(0)
{
}

Framebuffer::Framebuffer(GLenum type) : m_type(type), m_framebuffer(0),m_depth(0),m_texture(0),m_stencil(0)
{

}

Framebuffer::~Framebuffer()
{
	Destroy();
}

void Framebuffer::Destroy()
{
	if (m_framebuffer > 0) glDeleteFramebuffers(1,&m_framebuffer);

	if (m_texture > 0) glDeleteTextures(1,&m_texture);
	if (m_depth > 0) 
	{
		if (m_type & FRAMEBUFFER_DEPTH) glDeleteTextures(1,&m_depth);
		else glDeleteRenderbuffers(1,&m_depth);
	}
	if (m_stencil > 0) 
	{
		if (m_type & FRAMEBUFFER_STENCIL) glDeleteTextures(1,&m_stencil);
		else glDeleteRenderbuffers(1,&m_stencil);
	}
}

void Framebuffer::Init(unsigned int width, unsigned int height)
{
	Assert(m_type,"FRAME BUFFER ERROR: The frame buffer was not properly initialized prior to calling one of its functions.");
	Assert(!m_framebuffer,"FRAME BUFFER ERROR: Attempting to initialize a framebuffer that was already created.");

	/*
	m_framebuffer = 0;

	m_depth = Texture2D::GenerateTexture(width,height,GL_DEPTH24_STENCIL8);
	m_texture = Texture2D::GenerateTexture(width,height,GL_RGBA);

	//set up the frame buffer
	glGenFramebuffers(1,&m_framebuffer); 

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,m_framebuffer); //bind

	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,m_depth,0); 
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,m_texture,0); 


	GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
	printf("FRAMEBUFFER ERROR: %s\n", gluErrorString(glGetError()));
	Assert(0,"FRAMEBUFFER ERROR: Did not successfully create the framebuffer.");
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0); //unbind
	*/

	//glBindTexture(GL_TEXTURE_2D,m_depth);

	glGenFramebuffersEXT(1,&m_framebuffer);

	glBindFramebufferEXT(GL_FRAMEBUFFER,m_framebuffer);

	switch(m_type)
	{
	case FRAMEBUFFER_COLOR:
		m_texture = Texture2D::GenerateTexture(width,height,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE,TEXTURE_WRAP_REPEAT | TEXTURE_MINMAG_NEAREST);
		m_depth = Renderbuffer::GenerateRenderbuffer(width,height,GL_DEPTH_COMPONENT24);

		AttachTexture(GL_COLOR_ATTACHMENT0_EXT,m_texture);
		AttachRenderbuffer(GL_DEPTH_ATTACHMENT_EXT,m_depth);
		break;
	case FRAMEBUFFER_DEPTH:
		m_depth = Texture2D::GenerateTexture(width,height,GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT,GL_FLOAT,TEXTURE_WRAP_REPEAT | TEXTURE_MINMAG_NEAREST);
		AttachTexture(GL_DEPTH_ATTACHMENT_EXT,m_depth);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		break;
	case FRAMEBUFFER_COLOR | FRAMEBUFFER_DEPTH:
		AttachTexture(GL_COLOR_ATTACHMENT0,Texture2D::GenerateTexture(width,height,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE,TEXTURE_WRAP_REPEAT | TEXTURE_MINMAG_NEAREST));
		AttachTexture(GL_DEPTH_ATTACHMENT,Texture2D::GenerateTexture(width,height,GL_DEPTH_COMPONENT32,GL_DEPTH_COMPONENT,GL_UNSIGNED_INT,TEXTURE_WRAP_REPEAT | TEXTURE_MINMAG_NEAREST | TEXTURE_DEPTH_INTENSITY | TEXTURE_COMPAREMODE_RTOTEXTURE | TEXTURE_COMPAREFUNC_LEQUAL));
		break;
	case FRAMEBUFFER_COLOR | FRAMEBUFFER_DEPTH | FRAMEBUFFER_STENCIL:
		//AttachTexture(GL_COLOR_ATTACHMENT0,Texture2D::GenerateTexture(width,height,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE,TEXTURE_WRAP_REPEAT | TEXTURE_MINMAG_NEAREST));
		//AttachTexture(GL_DEPTH_ATTACHMENT,Texture2D::GenerateTexture(width,height,GL_DEPTH_COMPONENT32,GL_DEPTH_COMPONENT,GL_UNSIGNED_INT,TEXTURE_WRAP_REPEAT | TEXTURE_MINMAG_NEAREST | TEXTURE_DEPTH_INTENSITY | TEXTURE_COMPAREMODE_RTOTEXTURE | TEXTURE_COMPAREFUNC_LEQUAL));
		Assert(0,"NOT IMPLEMENTED ERROR");
		break;
	default:
		Assert(0,"FRAME BUFFER ERROR: Attempting to create a framebuffer of an unrecognized type.");
	}


	GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("FRAMEBUFFER ERROR: %s\n", gluErrorString(glGetError()));
		Assert(0,"FRAMEBUFFER ERROR: Did not successfully create the framebuffer.");
	}

	glBindFramebuffer(GL_FRAMEBUFFER,0);
	if (m_type & FRAMEBUFFER_DEPTH)
	{
		glDrawBuffer(GL_BACK);
		glReadBuffer(GL_BACK); 
	}
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	if (m_type & FRAMEBUFFER_DEPTH)
	{

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE); 
	}
}

void Framebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	if (m_type & FRAMEBUFFER_DEPTH)
	{
		glDrawBuffer(GL_BACK);
		glReadBuffer(GL_BACK);
	}
}

void Framebuffer::AttachTexture(GLenum attachmentPoint, GLuint texture)
{
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,attachmentPoint,GL_TEXTURE_2D,texture,0);
}

void Framebuffer::AttachRenderbuffer(GLenum attachmentPoint, GLuint renderbuffer)
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,attachmentPoint,GL_RENDERBUFFER,renderbuffer);
}