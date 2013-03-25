
#pragma once

#ifdef _dll_input_export_
#define declspec_input __declspec(dllexport)
#else
#define declspec_input __declspec(dllimport)
#endif

#include <bitset>

namespace myth
{
	namespace input
	{
		const char MOUSE_LEFT = 0x1;
		const char MOUSE_RIGHT = 0x2;
		const char MOUSE_MIDDLE = 0x4;
		const char MOUSE_SCROLLUP = 0x8;
		const char MOUSE_SCROLLDOWN = 0x10;
		const char MOUSE_XBUTTON = 0x20;

		class declspec_input MouseState
		{
		public:
			MouseState();
			~MouseState();

			void ClickButton(char key);
			void ReleaseButton(char key);

			void MoveMouse(float x, float y);
			float X() const;
			float Y() const;

			bool IsPressed(char key) const;
		private:
			float m_mousex, m_mousey;

			std::bitset<16> m_keys;
		};
	}
}