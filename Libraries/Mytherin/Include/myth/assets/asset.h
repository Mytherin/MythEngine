

#pragma once

#include <myth\io\loadable.h>
#include <myth\assets\assetdata.h>


namespace myth
{
	namespace assets
	{
		//! Specifies an asset
		class Asset
		{
		public:
			Asset(AssetData *assetData, int package) : m_data(assetData),m_package(package) { }
			virtual ~Asset(){ delete m_data; }

			virtual void Load() = 0;
			virtual void Reload() = 0;
			virtual void Destroy() = 0;
			virtual bool IsLoaded() = 0;
		protected:
			AssetData *m_data;
			int m_package;
		};

		//! Specifies an asset that can only be loaded from source code, if FilePath data is passed on the source code is read from the file
		class SourceAsset : public Asset
		{
		public:
			SourceAsset(AssetData *assetData, int package) : Asset(assetData,package) { }

			virtual void Load()
			{
				LoadFromSource(m_data->GetSource());
			}

			virtual void Reload()
			{
				ReloadFromSource(m_data->GetSource());
			}

			virtual void LoadFromSource(std::string source) = 0;
			virtual void ReloadFromSource(std::string source) = 0;
		};

		//! Specifies an asset that can only be loaded from a file path, only FilePath data may be passed on
		class FileAsset : public Asset
		{
		public:
			FileAsset(FilePath *assetData, int package) : Asset(assetData,package) { }

			virtual void Load()
			{
				LoadFromFile(m_data->AsString());
			}

			virtual void Reload()
			{
				ReloadFromFile(m_data->AsString());
			}

			virtual void LoadFromFile(std::string path) = 0;
			virtual void ReloadFromFile(std::string path) = 0;
		};
	}
}