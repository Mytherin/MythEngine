
#include <myth\assets\assetmanager.h>
#include <myth\debug\assert.h>

using namespace myth::containers;
using namespace myth::assets;
using namespace myth::io;

AssetManager::AssetManager() : 
	m_fileid(0)
{
	m_assets = new Dictionary<Dictionary<Asset*>*>(10);
	m_assets->Insert(0,new Dictionary<Asset*>(100));
}

int AssetManager::AddAsset(Asset *asset)
{
	Assert(asset,"ASSET INSERTION ERROR: A null pointer was provided.");

	int id = GetID();
	m_assets->Find(0)->Insert(id,asset);
	return id;
}

int AssetManager::AddAsset(int package, int id, Asset *asset)
{
	Assert(asset,"ASSET INSERTION ERROR: A null pointer was provided.");
	Assert(m_assets->Contains(package),"ASSET INSERTION ERROR: The specified package could not be found.");

	m_assets->Find(package)->Insert(id,asset);
	return id;
}

Asset* AssetManager::GetAsset(int package, int id)
{
	return m_assets->Find(package)->Find(id);
}

Asset* AssetManager::GetAsset(int id)
{
	return m_assets->Find(0)->Find(id);
}


bool AssetManager::Exists(int package, int id)
{
	Assert(m_assets->Contains(package), "ASSET ERROR: The specified package could not be found");
	return m_assets->Find(package)->Contains(id);
}