
#include <myth\resources\assetmanager.h>


using namespace myth::resources;
using namespace myth::io;

int AssetManager::AddAsset(short assetType,Source *sourceCode)
{
	int id = m_resourceManager.CreateAsset(assetType,sourceCode);


	return id;
}

int AssetManager::AddAsset(short assetType, FilePath *fileName)
{
	int id = m_resourceManager.CreateAsset(assetType,fileName);

	return id;
}