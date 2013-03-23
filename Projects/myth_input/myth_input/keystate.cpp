
#include <myth\input\keystate.h>

using namespace myth::input;

KeyState::KeyState()
{
}

KeyState::~KeyState()
{

}

void KeyState::PressKey(unsigned char key)
{
	m_keys[key] = true;
}
void KeyState::ReleaseKey(unsigned char key)
{
	m_keys[key] = false;
}

bool KeyState::IsPressed(unsigned char key) const
{
	return m_keys[key];
}