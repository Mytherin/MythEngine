
#include <myth\debug\assert.h>
#include <myth\os\windows\win32graphicsmanager.h>
#include <myth\os\windows\win32windowmanager.h>
#include <myth\window\windowoptions.h>
#include <Windows.h>

#include <myth\io\parser.h>

#include <iostream>
#include "testgraphics.h"

using namespace myth::io;
using namespace myth::os::windows;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	myth::window::WindowOptions options;

	options.Initialize(myth::window::WindowOptions::WINDOWED, 1024, 760, L"Mytherin", true);

	TestGraphics g = TestGraphics();
	
	return g_win32manager.Create(hInstance, hPrevInstance, lpCmdLine, nCmdShow, &g, options);
}

