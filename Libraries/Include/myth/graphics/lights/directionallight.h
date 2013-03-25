
#pragma once

#include <myth\graphics\light.h>
#include <myth\graphics\vertex.h>

namespace myth
{
	namespace graphics
	{
		struct DirectionalLight : Light
		{
		public:
			Vector3F ambientColor;
			Vector3F diffuseColor;
			Vector3F direction;
		};
	}
}