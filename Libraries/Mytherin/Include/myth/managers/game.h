
#pragma once

#ifdef _dll_managers_export_
#define declspec_managers __declspec(dllexport)
#else
#define declspec_managers __declspec(dllimport)
#endif

#include <myth\input\inputhandler.h>
#include <myth\window\resolution.h>

namespace myth
{
	namespace managers
	{
		const float FRAMETIME = 1.0f/60.0f;

		class declspec_managers Game
		{
		public:
			Game(){}
			virtual ~Game(){}

			virtual void LoadContent() = 0;
			virtual void UnloadContent() = 0;
			virtual void Input(myth::input::InputHandler& input) = 0;
			virtual void Update(float t) = 0;
			virtual void Draw(float t) = 0;
		};
	}
}