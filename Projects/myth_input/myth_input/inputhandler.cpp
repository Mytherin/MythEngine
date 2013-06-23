
#include <myth\input\inputhandler.h>

#include <iostream>

using namespace myth::input;

InputHandler::InputHandler():
	m_modifiers(0),m_keyState(KeyState()), m_mouseState(MouseState())
{
	m_prevMouseX = 0;
	m_prevMouseY = 0;
}

InputHandler::~InputHandler()
{

}

void InputHandler::Reset()
{
	m_prevMouseX = m_mouseState.X();
	m_prevMouseY = m_mouseState.Y();

	m_inputStream.Destroy();
	m_inputStream.Reset();
}


void InputHandler::PressModifier(ubyte modifier)
{
	m_modifiers = m_modifiers | modifier;
}

void InputHandler::ReleaseModifier(ubyte modifier)
{
	m_modifiers = m_modifiers & ~modifier;
}

//Keystate Functions
void InputHandler::PressKey(ubyte key)
{
	if (m_keyState.IsPressed(key)) return;
	m_inputStream.Push(InputEvent(key,KEYBOARD | PRESSKEY,m_modifiers));
	m_keyState.PressKey(key);
}
void InputHandler::ReleaseKey(ubyte key)
{
	if (!m_keyState.IsPressed(key)) return;
	m_inputStream.Push(InputEvent(key,KEYBOARD | RELEASEKEY,m_modifiers));
	m_keyState.ReleaseKey(key);
}
bool InputHandler::IsKeyPressed(ubyte key) const
{
	return m_keyState.IsPressed(key);
}
//Mousestate Functions
void InputHandler::MoveMouse(float x, float y)
{
	m_mouseState.MoveMouse(x,y);
}
void InputHandler::MouseClick(ubyte button)
{
	m_inputStream.Push(InputEvent(button,MOUSE | PRESSKEY,m_modifiers));
	m_mouseState.ClickButton(button);
}
void InputHandler::MouseRelease(ubyte button)
{
	m_inputStream.Push(InputEvent(button,MOUSE | RELEASEKEY,m_modifiers));
	m_mouseState.ReleaseButton(button);
}
bool InputHandler::IsMousePressed(ubyte button) const
{
	return m_mouseState.IsPressed(button); 
}
float InputHandler::GetMouseX() const
{
	return m_mouseState.X();
}
float InputHandler::GetMouseY() const
{
	return m_mouseState.Y();
}

float InputHandler::GetMouseOffsetX() const
{
	return m_mouseState.X() - m_prevMouseX;
}

float InputHandler::GetMouseOffsetY() const
{
	return m_mouseState.Y() - m_prevMouseY;
}

//KeyState & MouseState return functions
const KeyState& InputHandler::Keys() const
{
	return m_keyState;
}

const MouseState& InputHandler::Mouse() const
{
	return m_mouseState;
}

KeyState InputHandler::GetKeysCopy() const
{
	return KeyState(m_keyState);
}
MouseState InputHandler::GetMouseCopy() const
{
	return MouseState(m_mouseState);
}