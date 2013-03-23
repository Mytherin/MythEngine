

#include <GL\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>

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

using namespace myth::input;
using namespace myth::graphics;
using namespace myth::phys;

Texture *texture;
Framebuffer *frameBuffer;
SpotLight* spotLight, *spotLight2;
ShaderProgram *program;
Camera *camera;
Mesh *mesh;
Light *lights;
bool drag;

void TestGraphics::LoadContent()
{
	program = new ShaderProgram();
	program->LoadShaderFromFile(GL_VERTEX_SHADER,"specularspotlightshadow.vert");
	program->LoadShaderFromFile(GL_FRAGMENT_SHADER,"specularspotlightshadow.frag");
	program->Link();

	//int shaderProgram = g_assetManager.AddAsset(ASSET_SHADER_PROGRAM,source("v=\"specularspotlightshadow.vert\"; f=\"specularspotlightshadow.frag\";"));

	//HShaderProgram handle = g_assetManager.GetHandle<ShaderProgram>(shaderProgram);

	
	frameBuffer = new Framebuffer(GL_DEPTH_BUFFER);
	frameBuffer->Init(1024,760);

	program->Activate();

	program->PrintUniforms();

	texture = new Texture(GL_TEXTURE_2D,"error.png");
	texture->Load();

	Material *material = new Material();

	material->Ambient_Color = Vector3F(1,1,1);
	material->Diffuse_Color = Vector3F(1,1,1);
	material->Specular_Color = Vector3F(0.5f,0.5f,0.5f);
	material->Shininess = 1;
	material->Shininess_Strength = 10;

	mesh = new Mesh();
	//mesh->LoadMesh("phoenix_ugv.md2");
	mesh->LoadMesh("Plane.dae");
	mesh->SetMaterial(*material);
	//mesh->LoadTexture(*texture);


	camera = new Camera();
	camera->Perspective(75.0f,16.0f / 9.0f,0.1f,100.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CCW);

	drag = false;

	spotLight = new SpotLight();
	spotLight->ambientColor = Vector3(0.2f);
	spotLight->diffuseColor = Vector3(1.0f);
	spotLight->location = Vector3(0,0,5);
	spotLight->direction = Vector3(0,0,-1);
	spotLight->innerangle = 0.99f;
	spotLight->outerangle = 0.88f;
	spotLight->Constant = 1;
	spotLight->Linear = 0.0f;
	spotLight->Exp = 0.0f;

	g_lightManager.AddLight(spotLight);

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
			camera->MoveSideways(-1);
		}
		else if (inputEvent.IsKeyPress(KEY_ARROWRIGHT) || inputEvent.IsKeyPress(KeyFromChar('D')))
		{
			camera->MoveSideways(1);
		}
		else  if (inputEvent.IsKeyPress(KEY_ARROWUP) || inputEvent.IsKeyPress(KeyFromChar('W')))
		{
			camera->MoveForward(1);
		}
		else if (inputEvent.IsKeyPress(KEY_ARROWDOWN) || inputEvent.IsKeyPress(KeyFromChar('S')))
		{
			camera->MoveForward(-1);
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


	//program->Activate();
	//program->BindLights();
	//program->BindCamera(*camera);
	//program->BindModel(glm::mat4(1.0f));

	//Point p(spotLight->location.x,spotLight->location.y,spotLight->location.z);

	//frameBuffer->StartWrite();
	//
	//glClearColor(1.0f,0.0f,1.0f,1);
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//
	//program->BindTexture(texture->id(),0);

	//g_renderingManager.RenderPrimitive(Triangle(p,Point(p.x+1,p.y,p.z),Point(p.x,p.y+1,p.z)));

	//frameBuffer->EndWrite();
	//
	////program->BindTexture(frameBuffer->Texture(),0);

	//glClearColor(1.0f,0.5f,0.0f,1);
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//program->BindTexture(frameBuffer->GetTexture().id(),0);

	//g_renderingManager.RenderPrimitive(myth::phys::Rectangle(p,Point(p.x+1,p.y,p.z),Point(p.x,p.y+1,p.z)));



	Camera lightCamera;
	
	lightCamera.Perspective(75.0f,16.0f / 9.0f,0.1f,100.0f);
	lightCamera.SetPosition(spotLight->location);
	lightCamera.SetDirection(spotLight->direction);
	lightCamera.SetUp(glm::vec3(0,1,0));

	program->Activate();
	program->BindLights();
	program->BindCamera(lightCamera);
	program->BindModel(glm::mat4(1.0f));

	Point p(spotLight->location.x,spotLight->location.y,spotLight->location.z);

	frameBuffer->StartWrite();
	
	glClearColor(0.0f,0.0f,1.0f,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	program->BindTexture(texture->id(),0);
	program->BindModel(glm::translate(glm::vec3(0,0,0)) * glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f)) * glm::rotate(0.0f,glm::vec3(0.0f,0.0f,1.0f)));
	mesh->Render(*program);

	program->BindModel(glm::scale(glm::vec3(3,3,3)) * glm::translate(glm::vec3(0,0,5)) * glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f)) * glm::rotate(0.0f,glm::vec3(0.0f,0.0f,1.0f)));
	mesh->Render(*program);

	frameBuffer->EndWrite();
	
	glClearColor(1.0f,0.5f,0.0f,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	program->BindCamera(*camera);
	program->BindTexture(frameBuffer->GetDepth().id(),0);

	program->BindModel(glm::translate(glm::vec3(0,0,0)) * glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f)) * glm::rotate(0.0f,glm::vec3(0.0f,0.0f,1.0f)));
	mesh->Render(*program);

	program->BindModel(glm::scale(glm::vec3(3,3,3)) * glm::translate(glm::vec3(0,0,5)) * glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f)) * glm::rotate(0.0f,glm::vec3(0.0f,0.0f,1.0f)));
	mesh->Render(*program);
}