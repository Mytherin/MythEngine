
#pragma once

#include <myth\graphics\lightconstants.h>

namespace myth
{
	namespace graphics
	{
		struct UniformLocations
		{
		public:
			UniformLocations() : 
				Model(-1),View(-1),Projection(-1),MV(-1),MVP(-1),VP(-1),Ka(-1),Kd(-1),Ks(-1),SpecularPower(-1),SpecularIntensity(-1),EyePos(-1),EyeDir(-1)
			{}

			~UniformLocations()
			{
				delete [] directionalLight;
				delete [] pointLight;
				delete [] spotLight;
				delete [] Sampler;
			}

			//matrix uniform locations
			int Model;                 //Model->World matrix (mat4)
			int View;                  //World->View/Eye matrix (mat4)
			int Projection;            //View/Eye->Screenspace (projection matrix) (mat4)
			int MV;                    //Model-View matrix (View x Model) (mat4)
			int MVP;                   //Model-View-Projection (Projection x ModelView) (mat4)
			int VP;                    //View-Projection matrix (Projection x View) (mat4)

			//camera properties
			int EyePos;                //Camera Position (vec3)
			int EyeDir;                //Camera Direction (vec3)

			//material properties uniform locations
			int Ka;                    //Material Ambient Color (vec3)
			int Kd;                    //Material Diffuse Color (vec3)
			int Ks;                    //Material Specular Color (vec3)
			int SpecularPower;         //Material Specular Power (float)
			int SpecularIntensity;     //Material Specular Intensity (float)

			int DirectionalLights;     //Amount of directional lights whose data has been copied to the shader
			int PointLights;           //Amount of point lights whose data has been copied to the shader
			int SpotLights;            //Amount of spot lights whose data has been copied to the shader

			//maximum amounts of each light (not uniform variables)
			int maxdirectionalLights;
			int maxpointLights;
			int maxspotLights;

			//properties for each individual light
			DirectionalLightUL *directionalLight;
			PointLightUL *pointLight;
			SpotLightUL *spotLight;

			//texture sampler array
			int samplerCount; //amount of samplers supported
			int *Sampler; //array of uniform sampler locations (sampler2D)
		};
	}
}