
#include <myth\debug\assert.h>
#include <myth\input\keyvalues.h>
#include <myth\os\windows\win32filemanager.h>
#include <myth\os\windows\win32windowmanager.h>

#include <iostream>
#include <windowsx.h>
#include <vector>

using namespace myth::managers;
using namespace myth::input;
using namespace myth::window;
using namespace myth::os::windows;

const int WIN_BORDER_LEFT = -1;
const int WIN_BORDER_TOP = -1;
const int WIN_BORDER_RIGHT = 3;
const int WIN_BORDER_BOTTOM = 3;

Win32WindowManager::Win32WindowManager():
	WindowManager()
{
	AssertExecutionCount(1,"SINGLETON ERROR: A singleton instance of type Win32WindowManager has been initiated more than once");

	m_creatingWindow = false;
	m_hwnd = 0;
	m_hInstance = 0;
	m_game = 0;
	m_graphics = 0;
	m_fileManager = new Win32FileManager();
}

Win32WindowManager::~Win32WindowManager()
{
	delete m_graphics;
}

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int Win32WindowManager::Create(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow, Game* game, WindowOptions options)
{
	Assert(options.IsInitialized(),L"WIN32 LOAD ERROR: The windowed options have not been initialized. Please call WindowInitialize in the windowoptions.h file before creating a window.");

	m_showstyle = nCmdShow;

	AllocConsole();

	//initialize the options
	m_hInstance = hInstance;
	m_options = options;
	m_game = game;
	//generate the available resolutions of our current monitor
	GenerateAvailableResolutions();

	//create and register our window
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL,IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_options.m_title;
	wcex.hIconSm = LoadIcon(wcex.hInstance,MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		Assert(false,L"WIN32 LOAD ERROR: Failed to register the windows class.");
		return 1;
	}

	m_hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		m_options.m_title,
		m_options.m_title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_options.m_resolutionWidth,
		m_options.m_resolutionHeight,
		NULL,
		NULL,
		m_hInstance,
		NULL
		);

	//select the window style based on the options set
	SetScreenStyle(m_options.m_windowStyle);

	Assert(m_hwnd,L"WIN32 LOAD ERROR: Failed to create the hWnd");


	//initialize the opengl context
	m_graphics = new Win32GraphicsManager(m_hwnd);
	m_graphics->Create();

	//show the window
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	//initialize the game
	m_game->LoadContent();
	//start the message loop
	MSG msg;
	bool quit = false;
	while (!quit)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			//if there is a message, handle it
			if (msg.message == WM_QUIT)
			{
				quit = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//otherwise, draw and update the game and graphics
			m_game->Input(m_input);
			m_game->Update(FRAMETIME);
			m_game->Draw(FRAMETIME);
			m_graphics->SwapBuffer();
			m_input.Reset();
		}
	}
	//destroy the game and graphics
	m_game->UnloadContent();
	m_graphics->Destroy();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return g_win32manager.MessagePump(hWnd,message,wParam,lParam);
}

void Win32WindowManager::SetScreenStyle(wstyle screenStyle)
{
	Assert(m_hwnd,L"WIN32 LOAD ERROR: Attempting to change the shape of the window, but the window has not been created.");
	switch(screenStyle)
	{
	case WindowOptions::FULLSCREEN:
		SetFullscreen();
		break;
	case WindowOptions::WINDOWED:
		SetWindowed();
		break;
	default: 
		Assert(screenStyle == WindowOptions::WINDOWEDFULLSCREEN,L"WIN32 LOAD ERROR: The window style has been set to an invalid value. The window defaulted to Windowed Fullscreen");
		SetWindowedFullscreen();
	}

	ShowWindow(m_hwnd, m_showstyle);
	UpdateWindow(m_hwnd);
}

void Win32WindowManager::SetFullscreen()
{
	SetWindowedFullscreen();
}

void Win32WindowManager::SetWindowed()
{
	m_creatingWindow = true;
	m_options.m_windowStyle = WindowOptions::WINDOWED;

	SetWindowLongPtr(m_hwnd,GWL_STYLE,WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX);
	SetWindowLongPtr(m_hwnd,GWL_EXSTYLE,WS_EX_CLIENTEDGE);

	Monitor m = GetCurrentMonitor();
	MoveWindow(m_hwnd,
		m.m_left + (m.m_right-m.m_left)/2-m_options.m_resolutionWidth/2,
		m.m_top + (m.m_bottom-m.m_top)/2-m_options.m_resolutionHeight/2,
		m_options.m_resolutionWidth,m_options.m_resolutionHeight,true);

	ClipCursorToScreen(true);
	m_creatingWindow = false;
}

void Win32WindowManager::SetWindowedFullscreen()
{
	m_creatingWindow = true;
	m_options.m_windowStyle = WindowOptions::WINDOWEDFULLSCREEN;

	SetWindowLongPtr(m_hwnd,GWL_STYLE,WS_POPUP | WS_VISIBLE | WS_MINIMIZEBOX);
	SetWindowLongPtr(m_hwnd,GWL_EXSTYLE,WS_EX_CLIENTEDGE);

	Monitor m = GetCurrentMonitor();
	MoveWindow(m_hwnd,
		m.m_left + WIN_BORDER_LEFT,m.m_top + WIN_BORDER_TOP,
		m.m_right - m.m_left + WIN_BORDER_RIGHT,m.m_bottom - m.m_top + WIN_BORDER_BOTTOM,true);

	ClipCursorToScreen(true);
	m_creatingWindow = false;
}

void Win32WindowManager::SetResolution(int width, int height)
{
	m_options.m_resolutionWidth = width;
	m_options.m_resolutionHeight = height;
	switch(m_options.m_windowStyle)
	{
	case WindowOptions::WINDOWED:
		RECT windowRect;
		GetWindowRect(m_hwnd,&windowRect);
		MoveWindow(m_hwnd,windowRect.left,windowRect.top,width,height,true);
		break;
	case WindowOptions::FULLSCREEN:
		break;
	default:
		Assert(m_options.m_windowStyle == WindowOptions::WINDOWEDFULLSCREEN,L"WIN32 LOAD ERROR: The window style has been set to an invalid value. The window defaulted to Windowed Fullscreen");
		break;
	}
}

void Win32WindowManager::ClipCursorToScreen(bool clipCursor)
{
	if (m_options.m_windowStyle == WindowOptions::WINDOWED)
	{
		ClipCursor(NULL);
	}
	else
	{
		if (clipCursor && m_options.m_clipCursor)
		{
			RECT r;
			GetWindowRect(m_hwnd, &r);
			r.left -= WIN_BORDER_LEFT;
			r.right -= WIN_BORDER_RIGHT;
			r.top -= WIN_BORDER_TOP;
			r.bottom -= WIN_BORDER_BOTTOM;
			ClipCursor(&r);
		}
		else ClipCursor(NULL);
	}
}

InputEvent a = InputEvent(0,0,0);

LRESULT Win32WindowManager::MessagePump(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOVE:
		//if the window moves and it is set to windowed fullscreen, it means we swapped screens
		//set the window to windowed fullscreen again so it takes up the full window of the new screen
		if (m_options.m_windowStyle == WindowOptions::WINDOWEDFULLSCREEN && m_creatingWindow == false)
			SetWindowedFullscreen();
		break;
	case WM_KEYDOWN:
		Assert((wParam) >= 0 && (wParam) <= 255,L"ERROR: Key out of range.");
		switch(wParam)
		{
		case VK_CONTROL:
			m_input.PressModifier(CONTROL);
			break;
		case VK_SHIFT:
			m_input.PressModifier(SHIFT);
			break;
		case VK_MENU:
			m_input.PressModifier(ALT);
			break;
		default:
			m_input.PressKey((ubyte)(wParam));
		}
		break;
	case WM_KEYUP:
		Assert((wParam) >= 0 && (wParam) <= 255,L"ERROR: Key out of range.");
		switch(wParam)
		{
		case VK_CONTROL:
			m_input.ReleaseModifier(CONTROL);
			break;
		case VK_SHIFT:
			m_input.ReleaseModifier(SHIFT);
			break;
		case VK_MENU:
			m_input.ReleaseModifier(ALT);
			break;
		default:
			m_input.ReleaseKey((ubyte)(wParam));
		}
		break;
	case WM_LBUTTONDOWN:
		m_input.MouseClick(myth::input::MOUSE_LEFT); break;
	case WM_LBUTTONUP:
		m_input.MouseRelease(myth::input::MOUSE_LEFT); break;
	case WM_RBUTTONDOWN:
		m_input.MouseClick(myth::input::MOUSE_RIGHT); break;
	case WM_RBUTTONUP:
		m_input.MouseRelease(myth::input::MOUSE_RIGHT); break;
	case WM_MBUTTONDOWN:
		m_input.MouseClick(myth::input::MOUSE_MIDDLE); break;
	case WM_MBUTTONUP:
		m_input.MouseRelease(myth::input::MOUSE_MIDDLE); break;
	case WM_XBUTTONDOWN:
		m_input.MouseClick(myth::input::MOUSE_XBUTTON0 + HIWORD(wParam)); break;
	case WM_XBUTTONUP:
		m_input.MouseRelease(myth::input::MOUSE_XBUTTON0 + HIWORD(wParam)); break;
	case WM_MOUSEMOVE:
		m_input.MoveMouse(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		break;
	case WM_ACTIVATE:
		if (m_options.m_windowStyle == WindowOptions::WINDOWEDFULLSCREEN)
		{
			if (wParam == WA_INACTIVE)
			{
				ClipCursorToScreen(false);
			}
			else
			{
				ClipCursorToScreen(true);
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

Monitor Win32WindowManager::GetCurrentMonitor() const
{
	HMONITOR monitor = MonitorFromWindow(m_hwnd,MONITOR_DEFAULTTONEAREST);
	MONITORINFO info;
	info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor,&info);

	return Monitor(info.rcMonitor.left,info.rcMonitor.right,info.rcMonitor.top,info.rcMonitor.bottom);
}

void Win32WindowManager::GenerateAvailableResolutions()
{
	bool resolutionTaken = false;
	std::vector<Resolution> resolutions;
	Resolution newResolution;
	DEVMODE dm = { 0 };
	int count = 0;
	dm.dmSize = sizeof(dm);
	for(int i = 0; EnumDisplaySettings(NULL, i, &dm) != 0; ++i) 
	{
		newResolution = Resolution(dm.dmPelsWidth,dm.dmPelsHeight,dm.dmBitsPerPel,dm.dmDisplayFrequency);

		resolutionTaken = false;
		for(std::vector<Resolution>::iterator it = resolutions.begin(); it != resolutions.end(); ++it)
		{
			if (newResolution.Equals(*it))
			{
				resolutionTaken = true;
				break;
			}
		}

		if (!resolutionTaken)
		{
			resolutions.push_back(newResolution);
			count++;
		}
	}

	m_resolutionCount = count;
	m_resolutions = new Resolution[count];

	int i = 0;
	for(std::vector<Resolution>::iterator it = resolutions.begin(); it != resolutions.end(); ++it)
	{
		m_resolutions[i] = *it;
		++i;
	}
}