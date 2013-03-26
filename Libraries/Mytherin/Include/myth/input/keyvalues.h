

#pragma once

namespace myth
{
	namespace input
	{
		typedef unsigned char keycode;


		const keycode MOUSE_LEFT = 0x01;
		const keycode MOUSE_RIGHT = 0x02;
		const keycode MOUSE_MIDDLE = 0x04;
		const keycode MOUSE_SCROLLUP = 0x08;
		const keycode MOUSE_SCROLLDOWN = 0x10;
		const keycode MOUSE_XBUTTON0 = 0x1F;
		const keycode MOUSE_XBUTTON1 = 0x20;
		const keycode MOUSE_XBUTTON2 = 0x21;
		const keycode MOUSE_XBUTTON3 = 0x22;
		const keycode MOUSE_XBUTTON4 = 0x23;
		const keycode MOUSE_XBUTTON5 = 0x24;
		const keycode MOUSE_XBUTTON6 = 0x25;
		const keycode MOUSE_XBUTTON7 = 0x26;
		const keycode MOUSE_XBUTTON8 = 0x27;
		const keycode MOUSE_XBUTTON9 = 0x28;
		const keycode MOUSE_XBUTTON10 = 0x29;
		const keycode KEY_BACKSPACE = 0x08;
		const keycode KEY_TAB = 0x09;
		const keycode KEY_CLEAR = 0x0C;
		const keycode KEY_ENTER = 0x0D;
		const keycode KEY_PAUSE = 0x13;
		const keycode KEY_CAPSLOCK = 0x14;
		const keycode KEY_ESCAPE = 0x1B;
		const keycode KEY_SPACEBAR = 0x20;
		const keycode KEY_PAGEUP = 0x21;
		const keycode KEY_PAGEDOWN = 0x22;
		const keycode KEY_END = 0x23;
		const keycode KEY_HOME = 0x24;
		const keycode KEY_ARROWLEFT = 0x25;
		const keycode KEY_ARROWUP = 0x26;
		const keycode KEY_ARROWRIGHT = 0x27;
		const keycode KEY_ARROWDOWN = 0x28;
		const keycode KEY_PRINTSCREEN = 0x2C;
		const keycode KEY_INSERT = 0x2D;
		const keycode KEY_DELETE = 0x2E;
		const keycode KEY_NUM0 = 0x30;
		const keycode KEY_NUM1 = 0x31;
		const keycode KEY_NUM2 = 0x32;
		const keycode KEY_NUM3 = 0x33;
		const keycode KEY_NUM4 = 0x34;
		const keycode KEY_NUM5 = 0x35;
		const keycode KEY_NUM6 = 0x36;
		const keycode KEY_NUM7 = 0x37;
		const keycode KEY_NUM8 = 0x38;
		const keycode KEY_NUM9 = 0x39;
		const keycode KEY_CHAR_A = 0x41;
		const keycode KEY_CHAR_B = 0x42;
		const keycode KEY_CHAR_C = 0x43;
		const keycode KEY_CHAR_D = 0x44;
		const keycode KEY_CHAR_E = 0x45;
		const keycode KEY_CHAR_F = 0x46;
		const keycode KEY_CHAR_G = 0x47;
		const keycode KEY_CHAR_H = 0x48;
		const keycode KEY_CHAR_I = 0x49;
		const keycode KEY_CHAR_J = 0x4A;
		const keycode KEY_CHAR_K = 0x4B;
		const keycode KEY_CHAR_L = 0x4C;
		const keycode KEY_CHAR_M = 0x4D;
		const keycode KEY_CHAR_N = 0x4E;
		const keycode KEY_CHAR_O = 0x4F;
		const keycode KEY_CHAR_P = 0x50;
		const keycode KEY_CHAR_Q = 0x51;
		const keycode KEY_CHAR_R = 0x52;
		const keycode KEY_CHAR_S = 0x53;
		const keycode KEY_CHAR_T = 0x54;
		const keycode KEY_CHAR_U = 0x55;
		const keycode KEY_CHAR_V = 0x56;
		const keycode KEY_CHAR_W = 0x57;
		const keycode KEY_CHAR_X = 0x58;
		const keycode KEY_CHAR_Y = 0x59;
		const keycode KEY_CHAR_Z = 0x5A;
		const keycode KEY_LWINDOWS = 0x5B;
		const keycode KEY_RWINDOWS = 0x5C;
		const keycode KEY_NUMPAD0 = 0x60;
		const keycode KEY_NUMPAD1 = 0x61;
		const keycode KEY_NUMPAD2 = 0x62;
		const keycode KEY_NUMPAD3 = 0x63;
		const keycode KEY_NUMPAD4 = 0x64;
		const keycode KEY_NUMPAD5 = 0x65;
		const keycode KEY_NUMPAD6 = 0x66;
		const keycode KEY_NUMPAD7 = 0x67;
		const keycode KEY_NUMPAD8 = 0x68;
		const keycode KEY_NUMPAD9 = 0x69;
		const keycode KEY_MULTIPLY = 0x6A;
		const keycode KEY_ADD = 0x6B;
		const keycode KEY_SEPARATOR = 0x6C;
		const keycode KEY_SUBTRACT = 0x6D;
		const keycode KEY_DECIMAL =0x6E;
		const keycode KEY_DIVIDE = 0x6F;
		const keycode KEY_F1 = 0x70;
		const keycode KEY_F2 = 0x71;
		const keycode KEY_F3 = 0x72;
		const keycode KEY_F4 = 0x73;
		const keycode KEY_F5 = 0x74;
		const keycode KEY_F6 = 0x75;
		const keycode KEY_F7 = 0x76;
		const keycode KEY_F8 = 0x77;
		const keycode KEY_F9 = 0x78;
		const keycode KEY_F10 = 0x79;
		const keycode KEY_F11 = 0x7A;
		const keycode KEY_F12 = 0x7B;
		const keycode KEY_F13 = 0x7C;
		const keycode KEY_F14 = 0x7D;
		const keycode KEY_F15 = 0x7E;
		const keycode KEY_F16 = 0x7F;
		const keycode KEY_F17 = 0x80;
		const keycode KEY_F18 = 0x81;
		const keycode KEY_F19 = 0x82;
		const keycode KEY_F20 = 0x83;
		const keycode KEY_F21 = 0x84;
		const keycode KEY_F22 = 0x85;
		const keycode KEY_F23 = 0x86;
		const keycode KEY_F24 = 0x87;
		const keycode KEY_NUMLOCK = 0x90;
		const keycode KEY_SCROLLLOCK = 0x91;
		const keycode KEY_PLUS = 0xBB;
		const keycode KEY_COMMA = 0xBC;
		const keycode KEY_MINUS = 0xBD;
		const keycode KEY_PERIOD = 0xBE;
		const keycode KEY_OEM1 = 0xBA;
		const keycode KEY_OEM2 = 0xBF;
		const keycode KEY_OEM3 = 0xC0;
		const keycode KEY_OEM4 = 0xDB;
		const keycode KEY_OEM5 = 0xDC;
		const keycode KEY_OEM6 = 0xDD;
		const keycode KEY_OEM7 = 0xDE;
		const keycode KEY_OEM8 = 0xDF;
		const keycode KEY_OEM9 = 0xE2;

		inline keycode KeyFromChar(char letter)
		{
			if (letter >= 0x30 && letter <= 0x5A)
				return (keycode)letter;
			if (letter >= 0x61 && letter <= 0x7A)
				return (keycode)(letter - 0x20);
			return 0;
		}
	}
}