
#pragma once

namespace myth
{
	namespace window
	{
		typedef char wstyle;

		struct WindowOptions
		{
		public:
			WindowOptions(){}
			~WindowOptions(){}

			//! Available window styles
			enum { FULLSCREEN = 1, WINDOWED = 2, WINDOWEDFULLSCREEN = 3};

			void Initialize(wstyle ws, int resX, int resY, wchar_t* windowtitle, bool clipCursor)
			{
				m_windowStyle = ws;
				m_resolutionWidth = resX;
				m_resolutionHeight = resY;
				m_title = windowtitle;
				m_initialized = true;
				m_clipCursor = clipCursor;
			}

			bool IsInitialized()
			{
				return m_initialized;
			}

			//! Whether or not to clip the cursor to the window
			bool m_clipCursor;
			//! Variable containing the current window style
			wstyle m_windowStyle;
			//! The x-dimension of the resolution (x * y)
			int m_resolutionWidth;
			//! The y-dimension of the resolution (x * y)
			int m_resolutionHeight;
			//! The title of the window
			wchar_t* m_title;
		private:
			//! Variable indicating whether or not the options are initialized
			bool m_initialized;
		};
	}
}