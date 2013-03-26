

#pragma once

#ifdef _dll_input_export_
#define declspec_input __declspec(dllexport)
#else
#define declspec_input __declspec(dllimport)
#endif

#include "keystate.h"
#include "mousestate.h"
#include "inputstream.h"

namespace myth
{
	namespace input
	{
		class declspec_input InputHandler
		{
		public:
			InputHandler();
			~InputHandler();

			//! Resets the input handler, this should occur every frame otherwise unhandled input from previous frames will linger around
			void Reset();
			//! Pops the top input event from the stack, handling it
			InputEvent Pop(){return m_inputStream.Pop();}
			//! Peeks at the top input event, leaving it on the stack
			InputEvent Peek() const{return m_inputStream.Peek();}
			//! Returns if there is any available input
			bool Empty() const{return m_inputStream.Empty();}

			//! Presses a specified modifier
			void PressModifier(ubyte modifier);
			//! Releases a specified modifier
			void ReleaseModifier(ubyte modifier);
			//! Presses a specific key within the input handler
			void PressKey(ubyte key);
			//! Releases a specific key
			void ReleaseKey(ubyte key);
			//! Returns whether or not a specific key is pressed
			bool IsKeyPressed(ubyte key) const;

			//! Moves the mouse to the specified position
			void MoveMouse(float x, float y);
			//! Click a specific button on the mouse
			void MouseClick(ubyte button);
			//! Releases a specific button on the mouse
			void MouseRelease(ubyte button);
			//! Returns whether or not a specific mouse button is pressed
			bool IsMousePressed(ubyte key) const;

			//! Returns the mouse X
			float GetMouseX() const;
			//! Returns the mouse Y
			float GetMouseY() const;
			//! Returns the distance the mouse moved in the X direction since the last update
			float GetMouseOffsetX() const;
			//! Returns the distance the mouse moved in the Y direction since the last update
			float GetMouseOffsetY() const;

			//! Gets the keystate
			const KeyState& Keys() const;
			//! Gets the mousestate
			const MouseState& Mouse() const;

			//! Returns a copy of the current key state
			KeyState GetKeysCopy() const;
			//! Returns a copy of the current mouse state
			MouseState GetMouseCopy() const; 
		private:
			ubyte m_modifiers;

			float m_prevMouseX;
			float m_prevMouseY;

			KeyState m_keyState;
			MouseState m_mouseState;

			InputStream m_inputStream;
		};
	}
}