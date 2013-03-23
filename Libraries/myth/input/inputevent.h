
#pragma once

#ifdef _dll_input_export_
#define declspec_input __declspec(dllexport)
#else
#define declspec_input __declspec(dllimport)
#endif

namespace myth
{
	namespace input
	{
		typedef unsigned char ubyte;

		const ubyte KEYBOARD = 0x1;
		const ubyte MOUSE = 0x2;
		const ubyte JOYSTICK = 0x4;
		const ubyte GAMEPAD = 0x8;
		const ubyte PRESSKEY = 0x10;
		const ubyte RELEASEKEY = 0x20;

		const ubyte NONE = 0x0;
		const ubyte CONTROL = 0x1;
		const ubyte ALT = 0x2;
		const ubyte SHIFT = 0x4;

		class declspec_input InputEvent
		{
		public:
			//! Empty Constructor
			InputEvent(){}
			//! Initialization Constructor
			InputEvent(ubyte inputKey, ubyte type, ubyte modifiers) : m_type(type), m_inputKey(inputKey),m_modifiers(modifiers){}
			//! Destructor
			~InputEvent(){}

			bool Matches(const InputEvent& other) const
			{
				return m_type == other.m_type && m_inputKey == other.m_inputKey && m_modifiers == other.m_modifiers;
			}

			//! Returns whether or not this input event corresponds to a specific keyboard key being pressed without any modifiers (CTRL/ALT/SHIFT)
			bool IsKeyPress(ubyte key)
			{
				return m_inputKey == key && m_type == KEYBOARD | PRESSKEY && m_modifiers == NONE;
			}
			//! Returns whether or not this input event corresponds to a specific keyboard key being pressed with the specified modifiers
			bool IsKeyPress(ubyte key, ubyte mod)
			{
				return m_inputKey == key && m_type == KEYBOARD | PRESSKEY && m_modifiers == mod;
			}
			//! Returns whether or not this input event corresponds to a specific keyboard key being released without any modifiers (CTRL/ALT/SHIFT)
			bool IsKeyRelease(ubyte key)
			{
				return m_inputKey == key && m_type == KEYBOARD | RELEASEKEY && m_modifiers == NONE;
			}
			//! Returns whether or not this input event corresponds to a specific keyboard key being released with the specified modifiers
			bool IsKeyRelease(ubyte key, ubyte mod)
			{
				return m_inputKey == key && m_type == KEYBOARD | RELEASEKEY && m_modifiers == mod;
			}
			//! Returns whether or not this input event corresponds to a specific mouse button being pressed with any modifiers
			bool IsMousePress(ubyte mousebutton)
			{
				return m_inputKey == mousebutton && m_type == (MOUSE | PRESSKEY);
			}
			//! Returns whether or not this input event corresponds to a specific mouse button being released with any modifiers
			bool IsMouseRelease(ubyte mousebutton)
			{
				return m_inputKey == mousebutton && m_type == (MOUSE | RELEASEKEY);
			}
		//protected:
			ubyte m_inputKey;
			ubyte m_type;
			ubyte m_modifiers;
		};
	}
}