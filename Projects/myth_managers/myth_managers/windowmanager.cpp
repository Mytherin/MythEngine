
#include <myth\managers\windowmanager.h>

using namespace myth::input;
using namespace myth::managers;


const InputHandler& WindowManager::GetInput() const
{
	return m_input;
}
const KeyState& WindowManager::Keys() const
{
	return m_input.Keys();
}
const MouseState& WindowManager::Mouse() const
{
	return m_input.Mouse();
}
KeyState WindowManager::CopyKeyState() const
{
	return m_input.GetKeysCopy();
}
MouseState WindowManager::CopyMouseState() const
{
	return m_input.GetMouseCopy();
}

int WindowManager::ResolutionCount() const
{
	return m_resolutionCount;
}

myth::window::Resolution& WindowManager::GetResolution(int i) const
{
	return m_resolutions[i];
}