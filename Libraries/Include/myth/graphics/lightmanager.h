
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif

#include <myth\containers\list.h>
#include <myth\graphics\lights\directionallight.h>
#include <myth\graphics\lights\pointlight.h>
#include <myth\graphics\lights\spotlight.h>

namespace myth
{
	namespace graphics
	{
		class declspec_graphics LightManager
		{
		public:
			void AddLight(DirectionalLight *light) { DirectionalLights.Add(light);}
			void AddLight(PointLight *light){ PointLights.Add(light);}
			void AddLight(SpotLight *light){ SpotLights.Add(light);}

			void RemoveLight(DirectionalLight *light) { DirectionalLights.Remove(light);}
			void RemoveLight(PointLight *light) { PointLights.Remove(light);}
			void RemoveLight(SpotLight *light) { SpotLights.Remove(light);}

			void ClearLights();
			
			static LightManager& Instance()
			{
				static LightManager* m_instance = new LightManager;
				return *m_instance;
			}

			myth::containers::List<DirectionalLight*> DirectionalLights;
			myth::containers::List<PointLight*> PointLights;
			myth::containers::List<SpotLight*> SpotLights;
			
		private:
			LightManager();
			~LightManager();
		};

#define g_lightManager myth::graphics::LightManager::Instance()
	}
}