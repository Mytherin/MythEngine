
#pragma once

#ifdef _dll_resources_export_
#define declspec_resources __declspec(dllexport)
#else
#define declspec_resources __declspec(dllimport)
#endif

#include <myth\containers\dictionary.h>
#include <myth\resources\asset.h>

namespace myth
{
	namespace resources
	{
		class declspec_resources ResourceManager
		{
		public:
			ResourceManager();
			~ResourceManager();

			Asset* GetAsset(int package, int id);
			
			int CreateAsset(short type, AssetData *assetData);
		private:
			int GetID() { return m_fileid++; }

			containers::Dictionary<containers::Dictionary<Asset*>> m_assets;

			int m_fileid;
		};
	}
}