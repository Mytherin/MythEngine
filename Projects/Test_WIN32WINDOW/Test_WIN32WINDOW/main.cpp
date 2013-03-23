
#include <myth\os\windows\win32windowmanager.h>
#include <myth\window\windowoptions.h>
#include <Windows.h>

#include <iostream>
#include "WinGame.h"

using namespace myth::os::windows;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	myth::window::WindowOptions options;
	options.Initialize(myth::window::WindowOptions::WINDOWED,1024,640,L"Mytherin");

	WinGame g = WinGame();

	
	return g_win32manager.Create(hInstance,hPrevInstance,lpCmdLine,nCmdShow,&g,options);
}

