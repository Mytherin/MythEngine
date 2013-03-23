
#include <myth\graphics\graphics.h>

using namespace myth::graphics;

void Graphics::Create()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CW);
}