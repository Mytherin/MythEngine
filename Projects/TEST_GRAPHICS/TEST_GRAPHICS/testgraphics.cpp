

#include <GL\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>


#include <myth\resources\resourcemanager.h>
#include <myth\assets\assetmanager.h>
#include <myth\graphics\materials\materialtypes.h>
#include <myth\graphics\camera.h>
#include <myth\graphics\framebuffer.h>
#include <myth\graphics\light.h>
#include <myth\graphics\lightmanager.h>
#include <myth\graphics\shaderprogram.h>
#include <myth\graphics\modelmesh.h>
#include <myth\graphics\mesh.h>
#include <myth\graphics\skybox.h>
#include <myth\graphics\testmesh.h>
#include <myth\graphics\texture.h>
#include <myth\graphics\renderingmanager.h>
#include <myth\input\inputevent.h>
#include <myth\input\keyvalues.h>
#include "testgraphics.h"
#include <myth\phys\aabb.h>
#include <myth\phys\plane.h>
#include <myth\phys\rectangle.h>
#include <myth\phys\tetrahedron.h>
#include <myth\phys\triangle.h>
#include <myth\graphics\shadowfbo.h>

using namespace myth::assets;
using namespace myth::input;
using namespace myth::graphics;
using namespace myth::phys;
using namespace myth::resources;

Texture *texture, *normal, *flatnormal;
Texture *cubeMap;
Framebuffer *frameBuffer;
SpotLight* spotLight, *spotLight2;
ShaderProgram *program;
Camera *camera;
Camera *lightCamera;
Skybox *skybox;

Material *material = 0;
ModelMesh *mesh, *mm;
Light *lights;
bool drag;

void TestGraphics::LoadContent()
{
	int vertexShader = g_resourcemanager.CreateAsset(ASSET_VERTEX_SHADER,new FilePath("normalmapspotlight.vert"));
	int fragmentShader = g_resourcemanager.CreateAsset(ASSET_FRAGMENT_SHADER,new FilePath("normalmapspotlight.frag"));
	int shaderProgram = g_resourcemanager.CreateAsset(ASSET_SHADERPROGRAM,new Source(std::to_string(vertexShader) + "-" + std::to_string(fragmentShader)));
	program = g_assetManager.GetAsset<ShaderProgram>(shaderProgram);

	program->Load();
	
	skybox = new Skybox(new Source("texture = cubemap.png; shaders = (type:vert)(path:skybox.vert)-(type:frag)(path:skybox.frag); type = 2; size = 1;"),0);
	skybox->Load();

	program->PrintUniforms();

	texture = new Texture2D(new FilePath("error.png"),0);
	texture->Load();
	
	flatnormal = new Texture2D(new FilePath("error_flat_normal.png"),0);
	flatnormal->Load();

	normal = new Texture2D(new FilePath("error_normal.png"),0);
	normal->Load();

	cubeMap = new Texture3D(new FilePath("cubemap.png"),0);
	cubeMap->Load();

	material = new Material();

	material->Ambient_Color = Vector3F(1,1,1);
	material->Diffuse_Color = Vector3F(1,1,1);
	material->Specular_Color = Vector3F(0.5f,0.5f,0.5f);
	material->Shininess = 0;
	material->Shininess_Strength = 10;
	
	mesh = g_renderingManager.GeneratePrimitive(myth::phys::Rectangle(myth::phys::Point(-1,0,-1),myth::phys::Point(-1,0,1),myth::phys::Point(1,0,-1)));
	mm = g_renderingManager.GeneratePrimitive(AABB(-1,-1,-1,1,1,1));

	//mesh = new Mesh(new FilePath("Plane.dae"),0);
	//mesh->Load();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	drag = false;

	spotLight = new SpotLight();
	spotLight->ambientColor = Vector3(0.0f);
	spotLight->diffuseColor = Vector3(1.0f);
	spotLight->location = Vector3(0,0,-10);
	spotLight->direction = Vector3(0,0,1);
	spotLight->innerangle = 0.99f;
	spotLight->outerangle = 0.9f;
	spotLight->Constant = 1;
	spotLight->Linear = 0.00f;
	spotLight->Exp = 0.00f;

	g_lightManager.AddLight(spotLight);

	

	camera = new Camera();
	camera->Perspective(30.0f,16.0f / 9.0f,1.0f,100.0f);

	lightCamera = new Camera();
	lightCamera->Perspective(30.0f,16.0f / 9.0f,1.0f,100.0f);
	lightCamera->SetPosition(spotLight->location);
	lightCamera->SetDirection(spotLight->direction);
	lightCamera->SetUp(glm::vec3(0,1,0));

	/*
	spotLight2 = new SpotLight();
	spotLight2->ambientColor = Vector3(0.2f);
	spotLight2->diffuseColor = Vector3(1.0f);
	spotLight2->location = Vector3(10,0,5);
	spotLight2->direction = glm::normalize(Vector3(-2,0,-1));
	spotLight2->innerangle = 0.999f;
	spotLight2->outerangle = 0.70f;
	spotLight2->Constant = 1;
	spotLight2->Linear = 0.1f;
	spotLight2->Exp = 0.05f;

	g_lightManager.AddLight(spotLight2);*/
	
	camera->SetPosition(glm::vec3(15,0,50));
	camera->SetDirection(glm::normalize(glm::vec3(-1,0,-2)));
	camera->SetUp(glm::vec3(0,1,0));

	
	frameBuffer = new Framebuffer(FRAMEBUFFER_DEPTH);
	frameBuffer->Init(1024,760);
}

void TestGraphics::UnloadContent()
{
}

bool ShowBumpNormal = false;
void TestGraphics::Input(myth::input::InputHandler& input)
{
	myth::input::InputEvent inputEvent;
	
	float cameraspeed = 0.05f;	

	if (input.IsKeyPressed(KEY_ARROWLEFT) || input.IsKeyPressed(KeyFromChar('A')))
	{
		//spotLight->location.x--;
		camera->MoveSideways(-cameraspeed);
		//lightCamera->MoveSideways(-1);
	}
	else if (input.IsKeyPressed(KEY_ARROWRIGHT) || input.IsKeyPressed(KeyFromChar('D')))
	{
		//spotLight->location.x++;
		camera->MoveSideways(cameraspeed);
		//lightCamera->MoveSideways(1);
	}
	else  if (input.IsKeyPressed(KEY_ARROWUP) || input.IsKeyPressed(KeyFromChar('W')))
	{
		camera->MoveForward(cameraspeed);
		//lightCamera->MoveForward(1);
		//spotLight->location.z++;
	}
	else if (input.IsKeyPressed(KEY_ARROWDOWN) || input.IsKeyPressed(KeyFromChar('S')))
	{
		camera->MoveForward(-cameraspeed);
		//spotLight->location.z--;
	}
	else if (input.IsKeyPressed(KEY_CHAR_Q))
	{
		camera->MoveUp(cameraspeed);
	}
	else if (input.IsKeyPressed(KEY_CHAR_E))
	{
		camera->MoveUp(-cameraspeed);
	}
	while (!input.Empty())
	{
		inputEvent = input.Pop();

		if (inputEvent.IsMousePress(MOUSE_RIGHT))
		{
			drag = true;
		}
		else if (inputEvent.IsMouseRelease(MOUSE_RIGHT))
		{
			drag = false;
		}
		else if (inputEvent.IsKeyPress(KEY_CHAR_F))
		{
			ShowBumpNormal = !ShowBumpNormal;
		}
	}
	if (drag)
	{
		float x = input.GetMouseOffsetX();
		float y = input.GetMouseOffsetY();

		camera->Yaw(-x);
		camera->Pitch(-y);
	}
}

void TestGraphics::Update(float t)
{
}

float ang = 0;

void TestGraphics::Draw(float t)
{
	ang += 0.004f;

	float offsetX = cos(ang)*10;
	float offsetZ = sin(ang)*10;
	
	glClearColor(1.0f,0.5f,0.0f,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	skybox->BindCamera(camera);
	skybox->Render();

	program->Activate();
	program->BindLights();
	program->BindCamera(*camera);
	program->BindModel(glm::mat4(1.0f));
	program->BindTexture(*texture,0);
	if (ShowBumpNormal)
		program->BindTexture(*normal,1);
	else program->BindTexture(*flatnormal,1);
	program->BindMaterial(*material);

	program->BindModel(glm::translate(glm::vec3(0,0,10)));
	mm->Render();

	program->BindModel(glm::translate(glm::vec3(0,0,0)) * glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f)) * glm::rotate(0.0f,glm::vec3(0.0f,0.0f,1.0f)));
	mesh->Render();
	
	program->BindModel(glm::scale(glm::vec3(5,5,5)) * glm::translate(glm::vec3(0,0,5)) * glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f)) * glm::rotate(0.0f,glm::vec3(0.0f,0.0f,1.0f)));
	mesh->Render();

	program->Deactivate();
}