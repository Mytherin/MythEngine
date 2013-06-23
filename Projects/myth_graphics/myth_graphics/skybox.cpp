
#include <myth\debug\assert.h>
#include <myth\generic\numerics.h>
#include <myth\graphics\camera.h>
#include <myth\graphics\modelmesh.h>
#include <myth\graphics\renderingmanager.h>
#include <myth\graphics\shaderprogram.h>
#include <myth\graphics\skybox.h>
#include <myth\graphics\texture.h>
#include <myth\io\parser.h>
#include <myth\phys\aabb.h>

using namespace myth::graphics;
using namespace myth::io;

Skybox::Skybox() : 
	SourceAsset(0,0),m_texture(0), m_shaderProgram(0),m_camera(0),m_mesh(0)
{

}

Skybox::Skybox(myth::assets::AssetData *assetData, int package) : 
	SourceAsset(assetData,package), m_texture(0), m_shaderProgram(0), m_camera(0),m_mesh(0)
{
}

Skybox::~Skybox()
{
	Destroy();
}

void Skybox::LoadFromSource(std::string source)
{
	KeyValueMap map = Parser::ParseAssignments(source,"%n = %v;");

	Assert(map.count("texture"), "SKYBOX LOADING ERROR: Attempting to create a skybox without a cubemap texture specified");
	Assert(map.count("shaders"), "SKYBOX LOADING ERROR: Attempting to create a skybox without a shaderprogram specified.");
	Assert(map.count("type")   , "SKYBOX LOADING ERROR: Attempting to create a skybox without a shape type specified.");
	Assert(map.count("size")   , "SKYBOX LOADING ERROR: Attempting to create a skybox without a size specified.");

	m_texture = new Texture(GL_TEXTURE_CUBE_MAP,new myth::assets::FilePath(map["texture"]),m_package);
	m_texture->Load();
	m_shaderProgram = new ShaderProgram(new myth::assets::Source(map["shaders"]),m_package);
	m_shaderProgram->Load();
	m_size = Float::ParseString(map["size"]);
	SetType(UShort::ParseString(map["type"]));
}

void Skybox::SetType(unsigned short t)
{
	switch(t)
	{
	case SKYBOX_BOX:
		if (m_mesh) delete m_mesh;
		m_mesh = g_renderingManager.GeneratePrimitive(myth::phys::AABB(-m_size,-m_size,-m_size,m_size,m_size,m_size));
		break;
	case SKYBOX_SPHERE:
		if (m_mesh) delete m_mesh;

		break;
	default:
		Assert(0, "SKYBOX ERROR: Unrecognized skybox type.");
	}
}

void Skybox::ReloadFromSource(std::string source)
{
	Destroy();
	LoadFromSource(source);
}

void Skybox::Destroy()
{
	if (m_texture) delete m_texture;
	if (m_shaderProgram) delete m_shaderProgram;
	if (m_mesh) delete m_mesh;

	m_texture = 0;
	m_shaderProgram = 0;
	m_mesh = 0;
}

bool Skybox::IsLoaded()
{
	return m_texture;
}


void Skybox::BindCamera(Camera* camera)
{
	m_camera = camera;
}

void Skybox::Render()
{
	Assert(m_camera,"SKYBOX RENDERING ERROR: Attempting to render a skybox without a camera attached.");
	Assert(m_shaderProgram,"SKYBOX RENDERING ERROR: Attempting to render a skybox without a shader program attached.");
	Assert(m_texture,"SKYBOX RENDERING ERROR: Attempting to render a skybox without a texture attached.");

	GLint cullingMode, depthFunc;
	glGetIntegerv(GL_CULL_FACE_MODE,&cullingMode);
	glGetIntegerv(GL_DEPTH_FUNC,&depthFunc);
	
    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);
	
	m_shaderProgram->Activate();
	m_shaderProgram->BindTexture(*m_texture,0);
	m_shaderProgram->BindCamera(*m_camera);
	m_shaderProgram->BindModel(glm::translate(glm::vec3(
		m_camera->Position().x-m_size/2,
		m_camera->Position().y-m_size/2, 
		m_camera->Position().z-m_size/2)));

	m_mesh->Render();

	m_shaderProgram->Deactivate();

	glCullFace(cullingMode);
	glDepthFunc(depthFunc);
}