

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
#include <myth\graphics\mesh.h>
#include <myth\graphics\testmesh.h>
#include <myth\graphics\texture.h>
#include <myth\graphics\renderingmanager.h>
#include <myth\input\inputevent.h>
#include <myth\input\keyvalues.h>
#include "testgraphics.h"
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

Texture *texture;
Framebuffer *frameBuffer;
SpotLight* spotLight, *spotLight2;
ShaderProgram *program;
ShaderProgram *shadowProgram;
Camera *camera;
Camera *lightCamera;

Mesh *mesh;
Light *lights;
bool drag;

void TestGraphics::LoadContent()
{

	int vertexShaderS = g_resourcemanager.CreateAsset(ASSET_VERTEX_SHADER,new FilePath("shadowmaptechnique.vert"));
	int fragmentShaderS = g_resourcemanager.CreateAsset(ASSET_FRAGMENT_SHADER,new FilePath("shadowmaptechnique.frag"));
	int shaderProgramS = g_resourcemanager.CreateAsset(ASSET_SHADERPROGRAM,new Source(std::to_string(vertexShaderS) + ";" + std::to_string(fragmentShaderS)));
	shadowProgram = g_assetManager.GetAsset<ShaderProgram>(shaderProgramS);

	shadowProgram->Load();

	int vertexShader = g_resourcemanager.CreateAsset(ASSET_VERTEX_SHADER,new FilePath("shadowmaptechnique.vert"));
	int fragmentShader = g_resourcemanager.CreateAsset(ASSET_FRAGMENT_SHADER,new FilePath("shadowmaptechnique.frag"));
	int shaderProgram = g_resourcemanager.CreateAsset(ASSET_SHADERPROGRAM,new Source(std::to_string(vertexShader) + ";" + std::to_string(fragmentShader)));
	program = g_assetManager.GetAsset<ShaderProgram>(shaderProgram);

	program->Load();
	

	program->PrintUniforms();

	texture = new Texture2D(new FilePath("error.png"),0);
	texture->Load();

	Material *material = new Material();

	material->Ambient_Color = Vector3F(1,1,1);
	material->Diffuse_Color = Vector3F(1,1,1);
	material->Specular_Color = Vector3F(0.5f,0.5f,0.5f);
	material->Shininess = 0;
	material->Shininess_Strength = 10;
	
	mesh = new Mesh(new FilePath("Plane.dae"),0);
	mesh->Load();
	mesh->SetMaterial(*material);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CCW);

	drag = false;

	spotLight = new SpotLight();
	spotLight->ambientColor = Vector3(0.0f);
	spotLight->diffuseColor = Vector3(1.0f);
	spotLight->location = Vector3(0,0,-10);
	spotLight->direction = Vector3(0,0,1);
	spotLight->innerangle = 0.99f;
	spotLight->outerangle = 0.8f;
	spotLight->Constant = 1;
	spotLight->Linear = 0.00f;
	spotLight->Exp = 0.00f;

	g_lightManager.AddLight(spotLight);

	

	camera = new Camera();
	camera->Perspective(75.0f,16.0f / 9.0f,1.0f,100.0f);

	lightCamera = new Camera();
	lightCamera->Perspective(75.0f,16.0f / 9.0f,1.0f,100.0f);
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
	
	camera->SetPosition(spotLight->location);
	camera->SetDirection(spotLight->direction);
	camera->SetUp(glm::vec3(0,1,0));

	
	frameBuffer = new Framebuffer(FRAMEBUFFER_DEPTH);
	frameBuffer->Init(1024,760);
}

void TestGraphics::UnloadContent()
{
}

void TestGraphics::Input(myth::input::InputHandler& input)
{
	myth::input::InputEvent inputEvent;

	while (!input.Empty())
	{
		inputEvent = input.Pop();

		if (inputEvent.IsKeyPress(KEY_ARROWLEFT) || inputEvent.IsKeyPress(KeyFromChar('A')))
		{
			//spotLight->location.x--;
			camera->MoveSideways(-1);
			//lightCamera->MoveSideways(-1);
		}
		else if (inputEvent.IsKeyPress(KEY_ARROWRIGHT) || inputEvent.IsKeyPress(KeyFromChar('D')))
		{
			//spotLight->location.x++;
			camera->MoveSideways(1);
			//lightCamera->MoveSideways(1);
		}
		else  if (inputEvent.IsKeyPress(KEY_ARROWUP) || inputEvent.IsKeyPress(KeyFromChar('W')))
		{
			camera->MoveForward(1);
			//lightCamera->MoveForward(1);
			//spotLight->location.z++;
		}
		else if (inputEvent.IsKeyPress(KEY_ARROWDOWN) || inputEvent.IsKeyPress(KeyFromChar('S')))
		{
			camera->MoveForward(-1);
			//lightCamera->MoveForward(-1);
			//spotLight->location.z--;
		}
		else if (inputEvent.IsKeyPress(KEY_SPACEBAR))
		{
			camera->MoveUp(1);
		}
		else if (inputEvent.IsKeyPress(KEY_SPACEBAR,SHIFT))
		{
			camera->MoveUp(-1);
		}
		else if (inputEvent.IsMousePress(MOUSE_RIGHT))
		{
			drag = true;
		}
		else if (inputEvent.IsMouseRelease(MOUSE_RIGHT))
		{
			drag = false;
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
	
	shadowProgram->Activate();
	shadowProgram->BindCamera(*lightCamera);
	shadowProgram->BindModel(glm::mat4(1.0f));
	frameBuffer->Bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shadowProgram->BindModel(glm::translate(glm::vec3(0,0,0)) * glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f)) * glm::rotate(0.0f,glm::vec3(0.0f,0.0f,1.0f)));
	mesh->Render(*shadowProgram);

	shadowProgram->BindModel(glm::scale(glm::vec3(3,3,3)) * glm::translate(glm::vec3(0,0,5)) * glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f)) * glm::rotate(0.0f,glm::vec3(0.0f,0.0f,1.0f)));
	mesh->Render(*shadowProgram);

	frameBuffer->Unbind();
	shadowProgram->Deactivate();

	glClearColor(1.0f,0.5f,0.0f,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	program->Activate();
	program->NSetUniform("LightVP",lightCamera->ViewProjectionMatrix());
	program->BindLights();
	program->BindCamera(*camera);
	program->BindModel(glm::mat4(1.0f));
	program->Bind2DTexture(frameBuffer->GetDepth(),0);
	program->Bind2DTexture(texture->id(),1);

	program->BindModel(glm::translate(glm::vec3(0,0,0)) * glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f)) * glm::rotate(0.0f,glm::vec3(0.0f,0.0f,1.0f)));
	mesh->Render(*program);

	program->BindModel(glm::scale(glm::vec3(3,3,3)) * glm::translate(glm::vec3(0,0,5)) * glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f)) * glm::rotate(0.0f,glm::vec3(0.0f,0.0f,1.0f)));
	mesh->Render(*program);

	program->Deactivate();
}