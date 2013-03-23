
#include <myth\debug\assert.h>

#include <myth\os\windows\win32graphicsmanager.h>
using namespace myth::os::windows;

Win32GraphicsManager::Win32GraphicsManager(HWND hwnd):
	m_hwnd(hwnd)
{
}

Win32GraphicsManager::~Win32GraphicsManager()
{
	Destroy();
}

void Win32GraphicsManager::Create()
{
	//gets the device context
	m_hdc = GetDC(m_hwnd);
	Assert(m_hdc,L"HDC ERROR: Error obtaining HDC (Device Context)");

	// set the pixel format for the DC
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int format = ChoosePixelFormat(m_hdc, &pfd);

	SetPixelFormat(m_hdc,format,&pfd);

	// create the render context (RC)
	m_hrc = wglCreateContext(m_hdc);
	Assert(m_hrc,L"HRC ERROR: Error obtaining HRC (Rendering Context)");

	// make it the current render context
	wglMakeCurrent(m_hdc, m_hrc);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fprintf(stderr,"Error initializing GLEW: %s\n",glewGetErrorString(error));
	}
	Assert(error == GLEW_OK,L"GLEW INIT ERROR: Error initializing GLEW");
}


void Win32GraphicsManager::Destroy()
{
	if (m_hrc)
	{
		wglMakeCurrent(m_hdc,NULL);
		wglDeleteContext(m_hrc);
	}
	if (m_hdc)
	{
		ReleaseDC(m_hwnd,m_hdc);
	}

	m_hwnd = NULL;
	m_hrc = NULL;
	m_hdc = NULL;
}

void Win32GraphicsManager::SwapBuffer()
{
	SwapBuffers(m_hdc);
}