
#include <myth\input\mousestate.h>

using namespace myth::input;

MouseState::MouseState():
	m_mousex(0),m_mousey(0)
{
}

MouseState::~MouseState()
{
}

void MouseState::ClickButton(char key)
{
	m_keys[key] = true;
}
void MouseState::ReleaseButton(char key)
{
	m_keys[key] = false;
}

void MouseState::MoveMouse(float x, float y)
{
	m_mousex = x;
	m_mousey = y;
}

float MouseState::X() const
{
	return m_mousex;
}

float MouseState::Y() const
{
	return m_mousey;
}

bool MouseState::IsPressed(char key) const
{
	return m_keys[key];
}