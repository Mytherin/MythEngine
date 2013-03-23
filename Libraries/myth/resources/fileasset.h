

#pragma once

#include <myth\io\filemanager.h>
#include <myth\resources\asset.h>

namespace myth
{
	namespace resources
	{
		class FileAsset : public Asset
		{
		public:
			FileAsset(io::Loadable *asset, std::string filename) : m_filename(filename),Asset(asset) {}
			FileAsset(unsigned short type, std::string filename) : m_filename(filename),Asset(type) {}
			~FileAsset(){}

			void Load()
			{
				m_asset->Load(g_fileManager.ReadFile(m_filename));
			}

			void Unload()
			{
				m_asset->Destroy();
			}
		protected:
			std::string m_filename;
		};
	}
}