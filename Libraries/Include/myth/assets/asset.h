

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
			}

			void Reload()
			{
			}
			
			virtual void Load(std::string source) = 0;
			virtual void Reload(std::string source) = 0;
			virtual void Destroy() = 0;
			virtual bool IsLoaded() = 0;
		protected:
			AssetData *m_data;
			int m_package;
		};
	}
}