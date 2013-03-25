
#pragma once

#ifdef _dll_managers_export_
#define declspec_managers __declspec(dllexport)
#else
#define declspec_managers __declspec(dllimport)
#endif

#include <myth\input\inputhandler.h>
#include <myth\io\filemanager.h>
#include <myth\graphics\graphics.h>
#include <myth\managers\game.h>
#include <myth\window\monitor.h>
#include <myth\window\resolution.h>
#include <myth\window\windowoptions.h>


namespace myth
{
	namespace managers
	{
		class declspec_managers WindowManager
		{
		public:
			WindowManager() {}
			virtual ~WindowManager(){if (m_game) delete m_game;}

			//! Sets the window style of the window to windowed, fullscreen or windowed fullscreen
			virtual void SetScreenStyle(window::wstyle screenStyle) = 0;
			//! Sets the window to fullscreen
			virtual void SetFullscreen() = 0;
			//! Sets the window to windowed mode
			virtual void SetWindowed() = 0;
			//! Sets the window to fullscreen
			virtual void SetWindowedFullscreen() = 0;
			//! Sets the resolution of the window
			virtual void SetResolution(int width, int height) = 0;

			//! Gets the amount of available resolutions
			int ResolutionCount() const;
			//! Gets the resolution at the spot i
			myth::window::Resolution& GetResolution(int i) const;

			//! Returns the currently active monitor
			virtual myth::window::Monitor GetCurrentMonitor() const = 0;

			const input::InputHandler& GetInput() const;
			const input::KeyState& Keys() const;
			const input::MouseState& Mouse() const;
			input::KeyState CopyKeyState() const;
			input::MouseState CopyMouseState() const;

		protected:
			managers::Game* m_game;
			graphics::Graphics* m_graphics;
			io::FileManager* m_fileManager;

			input::InputHandler m_input;

			int m_resolutionCount;
			myth::window::Resolution* m_resolutions;

		};
	}
}