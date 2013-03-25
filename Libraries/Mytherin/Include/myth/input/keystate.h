
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
		class declspec_input KeyState
		{
		public:
			KeyState();
			~KeyState();

			void PressKey(unsigned char key);
			void ReleaseKey(unsigned char key);

			bool IsPressed(unsigned char key) const;
		private:
			std::bitset<256> m_keys;
		};
	}
}