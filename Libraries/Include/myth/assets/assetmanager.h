

#pragma once

#ifdef _dll_assets_export_
#define declspec_assets __declspec(dllexport)
#else
#define declspec_assets __declspec(dllimport)
#endif

#include <myth\containers\dictionary.h>
#include <myth\assets\asset.h>
#include <myth\assets\assetdata.h>

namespace myth
{
	namespace assets
	{
		class declspec_assets AssetManager
		{
		public:
			template <class T>
			T* GetAsset(int package, int id)
			{
				return (T*)GetAsset(package,id);
			}

			Asset* GetAsset(int package, int id);
			
			//! Adds an asset to the local package (package 0) and returns the ID it was assigned
			int AddAsset(Asset* asset);

			//! Adds an asset with the specified package/id to the asset manager
			int AddAsset(int package, int id, Asset* asset);

			//! Returns true if the asset with the specified id exists within the specified package, and false otherwise
			bool Exists(int package, int id);

			static AssetManager& Instance()
			{
				static AssetManager* instance = new AssetManager();
				return *instance;
			}
		private:
			AssetManager();
			~AssetManager();
			

			int GetID() { return m_fileid++; }

			containers::Dictionary<containers::Dictionary<Asset*>> m_assets;

			int m_fileid;
		};

#define g_assetManager myth::assets::AssetManager::Instance()
	}
}