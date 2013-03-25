
#pragma once

#ifdef _dll_resources_export_
#define declspec_resources __declspec(dllexport)
#else
#define declspec_resources __declspec(dllimport)
#endif

#include <myth\containers\dictionary.h>
#include <myth\assets\asset.h>
#include <myth\assets\assetdata.h>

namespace myth
{
	namespace resources
	{
		class declspec_resources ResourceManager
		{
		public:
			ResourceManager();
			~ResourceManager();

			//! Creates an asset of the specified file type with the specified asset data in the specified package directory with the specified id
			/*!
			\param type The asset type. A list of all asset types is given in <myth\assets\assetdata.h>
			\param assetData The asset data 
			\param package The package number
			\param id The unique identifier of the asset
			\return Returns the ID of the stored asset, or -1 if the asset type was invalid
			*/
			int CreateAsset(short type, assets::AssetData *assetData, int package, int id);

			//! Creates an asset of the specified file type with the specified asset data in the local asset directory (package #0) with a generated ID
			/*!
			\param type The asset type. A list of all asset types is given in <myth\assets\assetdata.h>
			\param assetData The asset data 
			\return Returns the ID of the stored asset, or -1 if the asset type was invalid
			*/
			int CreateAsset(short type, assets::AssetData *assetData);
			
			//int AddAsset(short assetType,assets::Source *sourceCode);
			//int AddAsset(short assetType, assets::FilePath *fileName);
		private:
		};
	}
}