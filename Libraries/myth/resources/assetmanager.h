

#pragma once

#ifdef _dll_resources_export_
#define declspec_resources __declspec(dllexport)
#else
#define declspec_resources __declspec(dllimport)
#endif

#include <myth\containers\dictionary.h>
#include <myth\resources\asset.h>
#include <myth\resources\source.h>
#include <myth\resources\resourcemanager.h>

namespace myth
{
	namespace resources
	{
		class declspec_resources AssetManager
		{
		public:
			int AddAsset(short assetType,Source *sourceCode);
			int AddAsset(short assetType, FilePath *fileName);

			template <class T>
			T* GetAsset(int package, int id)
			{
				return (T*)m_resourceManager.GetAsset(package,id);
			}

			static AssetManager& Instance()
			{
				static AssetManager* instance = new AssetManager();
				return *instance;
			}
		private:
			AssetManager() {}
			~AssetManager(){}
			
			ResourceManager m_resourceManager;
		};

#define g_assetManager myth::resources::AssetManager::Instance()
	}
}