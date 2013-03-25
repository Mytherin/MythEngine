
#include <myth\resources\resourcemanager.h>

#include <myth\graphics\shader.h>
#include <myth\graphics\shaderprogram.h>

#include <myth\assets\assetmanager.h>

using namespace myth::assets;
using namespace myth::resources;


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{

}

int ResourceManager::CreateAsset(short type, AssetData *assetData)
{
	Asset* asset(0);

	switch (type)
	{
	case ASSET_FRAGMENT_SHADER:
		asset = new myth::graphics::FragmentShader(assetData,0);
		break;
	case ASSET_VERTEX_SHADER:
		asset = new myth::graphics::VertexShader(assetData,0);
		break;
	case ASSET_SHADERPROGRAM:
		asset = new myth::graphics::ShaderProgram(assetData,0);
		break;
	default: return -1;
	}


	int id = g_assetManager.AddAsset(asset);


	return id;
}

