#pragma once

#ifdef _dll_oswindows_export_
#define declspec_oswindows __declspec(dllexport)
#else
#define declspec_oswindows __declspec(dllimport)
#endif

#include <myth\managers\windowmanager.h>
#include <myth\os\windows\win32graphicsmanager.h>
#include <myth\window\monitor.h>
#include <myth\window\windowoptions.h>

#include <Windows.h>

namespace myth
{
	//! Contains all OS specific functions and classes
	namespace os
	{
		//! Contains all classes and functions specific to windows
		namespace windows
		{
			typedef int windowShowStyle;

			//! The Win32WindowManager creates and manages a window using the WIN32 API in the Windows OS
			class declspec_oswindows Win32WindowManager : public managers::WindowManager
			{
			public:
				int Create(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow, managers::Game* game, window::WindowOptions options);

				void SetScreenStyle(window::wstyle screenStyle);
				//! Sets the program to fullscreen
				void SetFullscreen() final;
				//! Sets the program to windowed mode
				void SetWindowed() final;
				//! Sets the program to windowed fullscreen
				void SetWindowedFullscreen() final;
				//! Sets the resolution to the width and the height
				void SetResolution(int width, int height) final;

				//! Generates the resolutions available on the target monitor
				void GenerateAvailableResolutions();

				static Win32WindowManager& Instance()
				{
					static Win32WindowManager* m_instance = new Win32WindowManager;
					return *m_instance;
				}


				//! Sets whether to clip the cursor to the screen or not
				void ClipCursorToScreen(bool clipCursor);
				//! Returns the currently active monitor
				myth::window::Monitor GetCurrentMonitor() const;

				LRESULT MessagePump(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			protected:
				HWND m_hwnd;
				window::WindowOptions m_options;
				windowShowStyle m_showstyle;
				HINSTANCE m_hInstance;
			private:
				bool m_creatingWindow;

				Win32WindowManager();
				~Win32WindowManager();
			};

#define g_win32manager myth::os::windows::Win32WindowManager::Instance()
		}
	}
}