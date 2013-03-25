
#pragma once

#include <myth\graphics\light.h>
#include <myth\graphics\vertex.h>

namespace myth
{
	namespace graphics
	{
		struct PointLight : Light
		{
		public:
			Vector3F ambientColor;
			Vector3F diffuseColor;
			Vector3F location;
			float Constant;
			float Linear;
			float Exp;
		};
	}
}