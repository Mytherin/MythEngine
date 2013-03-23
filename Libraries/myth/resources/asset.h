

#pragma once

#include <myth\io\loadable.h>
#include <myth\resources\source.h>


namespace myth
{
	namespace resources
	{
		class Asset
		{
			friend class ResourceManager;

		public:
			Asset(AssetData *assetData, int package) : m_data(assetData),m_package(package) { }
			virtual ~Asset(){ delete m_data; }

			void Load();
			void Unload();

		protected:
			virtual void Load(std::string source);
			virtual void Reload(std::string source);
			virtual void Destroy();
			virtual bool IsLoaded();

			AssetData *m_data;
			int m_package;
		};
	}
}