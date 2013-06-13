
#include <myth\graphics\renderbuffer.h>

using namespace myth::graphics;

GLuint Renderbuffer::GenerateRenderbuffer(unsigned int width, unsigned int height, GLenum dataType)
{
	GLuint renderbuffer(0);

	glGenRenderbuffers(1,&renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER,renderbuffer);

	glRenderbufferStorage(GL_RENDERBUFFER,dataType,width,height);

	glBindRenderbuffer(GL_RENDERBUFFER,0);
	return renderbuffer;
}