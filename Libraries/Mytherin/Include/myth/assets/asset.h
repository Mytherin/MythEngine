

#pragma once

#include <myth\io\loadable.h>
#include <myth\assets\assetdata.h>


namespace myth
{
	namespace assets
	{
		class Asset
		{
		public:
			Asset(AssetData *assetData, int package) : m_data(assetData),m_package(package) { }
			virtual ~Asset(){ delete m_data; }

			void Load()
			{
				LoadFromSource(m_data->GetSource());
			}

			void Reload()
			{
				ReloadFromSource(m_data->GetSource());
			}
			
			virtual void LoadFromSource(std::string source) = 0;
			virtual void ReloadFromSource(std::string source) = 0;
			virtual void Destroy() = 0;
			virtual bool IsLoaded() = 0;
		protected:
			AssetData *m_data;
			int m_package;
		};
	}
}