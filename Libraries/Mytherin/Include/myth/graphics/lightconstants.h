
#pragma once

namespace myth
{
	namespace graphics
	{
		struct DirectionalLightUL
		{
		public:
			DirectionalLightUL() : La(-1),Ld(-1),Direction(-1){}

			int La;                    //Ambient Color of the light (vec3)
			int Ld;                    //Diffuse Color of the light (vec3)
			int Direction;             //Direction of the light (vec3)
		};

		struct PointLightUL
		{
		public:
			PointLightUL() : La(-1),Ld(-1),Location(-1), Constant(-1), Linear(-1), Exp(-1)
			{}

			int La;                    //Ambient Color of the light (vec3)
			int Ld;                    //Diffuse Color of the light (vec3)
			int Location;              //Location of the light (vec3)

			int Constant;             //Constant Attenuation Factor of the point-light (float)
			int Linear;               //Linear Attenuation Factor of the point-light (float)
			int Exp;                  //Exponential Attenuation Factor of the point-light (float)
		};

		struct SpotLightUL
		{
		public:
			SpotLightUL() : La(-1),Ld(-1),Location(-1),OuterAngle(-1),InnerAngle(-1),Direction(-1), Constant(-1), Linear(-1), Exp(-1)
			{}

			int La;                    //Ambient Color of the light (vec3)
			int Ld;                    //Diffuse Color of the light (vec3)
			int Location;              //Location of the light (vec3)
			int Direction;             //Direction of the light (vec3)
			int InnerAngle;            //The inner angle of the light, aka the angle in which the light is brightest (float [-1..1] as cos(angle))
			int OuterAngle;            //The outer angle of the light, the light gradually falls off between the inner and outer angle (float [-1..1] as cos(angle))

			int Constant;             //Constant Attenuation Factor of the point-light (float)
			int Linear;               //Linear Attenuation Factor of the point-light (float)
			int Exp;                  //Exponential Attenuation Factor of the point-light (float)
		};
	}
}