
#pragma once

#include <myth\graphics\light.h>
#include <myth\graphics\vertex.h>


namespace myth
{
	namespace graphics
	{
		struct SpotLight : Light
		{
		public:
			Vector3F ambientColor;
			Vector3F diffuseColor;
			Vector3F location;
			Vector3F direction;
			float innerangle;   
			float outerangle;
			float Constant;
			float Linear;
			float Exp;
		};
	}
}