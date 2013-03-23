
#include <myth\debug\assert.h>
#include <myth\graphics\lightmanager.h>

using namespace myth::containers;
using namespace myth::graphics;

LightManager::LightManager()
{
	AssertExecutionCount(1,"SINGLETON ERROR: A singleton instance of type LightManager has been initiated more than once");
}

LightManager::~LightManager()
{
}

void LightManager::ClearLights()
{
	DirectionalLights.Clear();
	PointLights.Clear();
	SpotLights.Clear();
}