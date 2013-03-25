
#pragma once

#include <string>
#include <myth\graphics\vertex.h>

namespace myth
{
	namespace graphics
	{
		struct Material
		{
			Material() : Opacity(1.0f),Shininess(0.0f),Shininess_Strength(1.0f),Twosided(false){}
			Material(Vector3F Color, float SpecularIntensity, float SpecularStrength) 
				: Diffuse_Color(Color),Ambient_Color(Color),Specular_Color(Vector3F(1.0f)),Twosided(false),Opacity(1.0f),Shininess(SpecularIntensity),Shininess_Strength(SpecularStrength)
			{}
			~Material(){}

			std::string Name;

			Vector3F Diffuse_Color;
			Vector3F Specular_Color;
			Vector3F Ambient_Color;

			bool Twosided;

			float Opacity;
			float Shininess;
			float Shininess_Strength;

		};
	}
}