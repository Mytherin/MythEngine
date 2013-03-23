
#pragma once

#include <myth\graphics\material.h>

namespace myth
{
	namespace graphics
	{
		const Material GrayMetal = Material(Vector3F(0.6f,0.6f,0.6f),10.0f,25.0f);
		const Material RedPlastic = Material(Vector3F(0.8f,0.2f,0.2f),0.0f,0.0f);
		const Material Stone = Material(Vector3F(0.8f,0.8f,0.8f),0.0f,0.0f);
		const Material Wood = Material(Vector3F(0.7f,0.35f,0.0f),0.0f,0.0f);	
	}
}