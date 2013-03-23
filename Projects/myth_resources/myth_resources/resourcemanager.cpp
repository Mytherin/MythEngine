
#include <myth\resources\resourcemanager.h>

#include <myth\graphics\shader.h>
#include <myth\graphics\shaderprogram.h>

#include <myth\resources\assettypes.h>

using namespace myth::containers;
using namespace myth::resources;


ResourceManager::ResourceManager() : 
	m_assets(Dictionary<Dictionary<Asset*>>(10)), m_fileid(0)
{
	m_assets.Insert(0,Dictionary<Asset*>(100));
}

ResourceManager::~ResourceManager()
{

}

int ResourceManager::CreateAsset(short type, AssetData *assetData)
{
	int id = GetID();
	int package = 0;

	switch (type)
	{
	case ASSET_FRAGMENT_SHADER:
		m_assets[package].Insert(id,new myth::graphics::FragmentShader(assetData,package));
		return id;
	case ASSET_VERTEX_SHADER:
		m_assets[package].Insert(id,new myth::graphics::VertexShader(assetData,package));
		return id;
	case ASSET_SHADERPROGRAM:
		m_assets[package].Insert(id,new myth::graphics::ShaderProgram(assetData,package));
		return id;
	}
	return -1;
}


Asset* ResourceManager::GetAsset(int package, int id)
{
	return m_assets[package][id];
}