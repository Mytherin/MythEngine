
#pragma once

#ifdef _dll_oswindows_export_
#define declspec_oswindows __declspec(dllexport)
#else
#define declspec_oswindows __declspec(dllimport)
#endif

#include <myth\graphics\graphics.h>
#include <Windows.h>

namespace myth
{
	namespace os
	{
		namespace windows
		{
			class declspec_oswindows Win32GraphicsManager : public graphics::Graphics
			{
			public:
				//! Empty constructor for the graphics manager
				Win32GraphicsManager(HWND hwnd);
				//! Destructor
				~Win32GraphicsManager();

				//! Creates the Graphics Manager
				void Create();
				//! Destroys the Graphics Manager
				void Destroy();
				//! Swaps the buffers of the device
				void SwapBuffer();
			private:
				HWND m_hwnd;
				HDC m_hdc;
				HGLRC m_hrc;
			};
		}
	}
}