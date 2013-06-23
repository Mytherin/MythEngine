
#include <myth\debug\assert.h>

#include <myth\phys\aabb.h>
#include <myth\phys\line.h>
#include <myth\phys\linesegment.h>
#include <myth\phys\obb.h>
#include <myth\phys\plane.h>
#include <myth\phys\polyhedron.h>
#include <myth\phys\pointcloud.h>
#include <myth\phys\rectangle.h>
#include <myth\phys\sphere.h>
#include <myth\phys\tetrahedron.h>
#include <myth\phys\triangle.h>
#include <myth\graphics\modelmesh.h>
#include <myth\graphics\renderingmanager.h>

using namespace myth::phys;
using namespace myth::graphics;


RenderingManager::RenderingManager()
{
}

RenderingManager::~RenderingManager()
{
}


ModelMesh* RenderingManager::GeneratePrimitive(AABB aabb)
{
	Point A = aabb.m_center + Point( aabb.m_size.x,  aabb.m_size.y,  aabb.m_size.z);
	Point B = aabb.m_center + Point(-aabb.m_size.x,  aabb.m_size.y,  aabb.m_size.z);
	Point C = aabb.m_center + Point( aabb.m_size.x, -aabb.m_size.y,  aabb.m_size.z);
	Point D = aabb.m_center + Point(-aabb.m_size.x, -aabb.m_size.y,  aabb.m_size.z);
	Point E = aabb.m_center + Point( aabb.m_size.x,  aabb.m_size.y, -aabb.m_size.z);
	Point F = aabb.m_center + Point(-aabb.m_size.x,  aabb.m_size.y, -aabb.m_size.z);
	Point G = aabb.m_center + Point( aabb.m_size.x, -aabb.m_size.y, -aabb.m_size.z);
	Point H = aabb.m_center + Point(-aabb.m_size.x, -aabb.m_size.y, -aabb.m_size.z);

	Normal FRONTN = glm::normalize(E-A);
	Normal BACKN = glm::normalize(A-E);
	Normal TOPN = glm::normalize(C-A);
	Normal BOTN = glm::normalize(A-C);
	Normal LEFTN = glm::normalize(B-A);
	Normal RIGHTN = glm::normalize(A-B);

	ModelMesh *mesh = new ModelMesh();

	/*Point points[] = {A,B,C,D,E,F,G,H};

	float sqrt3 = 1 / sqrt(3);
	//for every vertex normal, subtract the point from the complete opposite point on the cube
	Normal normals[] = {
		Normal( sqrt3,  sqrt3,  sqrt3),
		Normal(-sqrt3,  sqrt3,  sqrt3),
		Normal( sqrt3, -sqrt3,  sqrt3),
		Normal(-sqrt3, -sqrt3,  sqrt3),
		Normal( sqrt3,  sqrt3, -sqrt3),
		Normal(-sqrt3,  sqrt3, -sqrt3),
		Normal( sqrt3, -sqrt3, -sqrt3),
		Normal(-sqrt3, -sqrt3, -sqrt3),

	};
	TexCoord texcoords[] = {
		TexCoord(0,0),
		TexCoord(1,0),
		TexCoord(0,1),
		TexCoord(1,1),
		TexCoord(1,1),
		TexCoord(0,1),
		TexCoord(1,0),
		TexCoord(0,0)
	};

	unsigned short indices[] = 
	{
		0,1,2,       //ABCD quad [front]
		3,2,1,   
		4,5,6,       //EFGH quad [back]
		7,6,5,
		1,5,3,       //BDFH quad [side]
		7,3,5,
		4,0,2,       //ACEG quad [side]
		6,2,0,
		4,5,0,       //ABEF quad [top]
		1,0,5,
		3,2,7,       //CDGH quad [bottom]      
		6,7,2
	};*/
	
	Point points[] = {
		A,B,C,D,       //ABCD quad [front]         
		E,F,G,H,       //EFGH quad [back]
		B,D,F,H,       //BDFH quad [left side]
		A,C,E,G,       //ACEG quad [right side]
		A,B,E,F,       //ABEF quad [top]
		C,D,G,H};      //CDGH quad [bottom]    
	Normal normals[] = {
		FRONTN,FRONTN,FRONTN,FRONTN,
		BACKN,BACKN,BACKN,BACKN,
		LEFTN,LEFTN,LEFTN,LEFTN,
		RIGHTN,RIGHTN,RIGHTN,RIGHTN,
		TOPN,TOPN,TOPN,TOPN,
		BOTN,BOTN,BOTN,BOTN
	};
	TexCoord texcoords[] = {
		TexCoord(0,0),TexCoord(1,0),TexCoord(0,1),TexCoord(1,1),
		TexCoord(0,0),TexCoord(1,0),TexCoord(0,1),TexCoord(1,1),
		TexCoord(0,0),TexCoord(1,0),TexCoord(0,1),TexCoord(1,1),
		TexCoord(0,0),TexCoord(1,0),TexCoord(0,1),TexCoord(1,1),
		TexCoord(0,0),TexCoord(1,0),TexCoord(0,1),TexCoord(1,1),
		TexCoord(0,0),TexCoord(1,0),TexCoord(0,1),TexCoord(1,1)
	};

	unsigned short indices[] = 
	{
		0,1,2,3,2,1,
		4,5,6,7,6,5,
		8,9,10,11,10,9,
		12,13,14,15,14,13,
		16,17,18,19,18,17,
		20,21,22,23,22,21
	};

	mesh->Initialize(points,texcoords,normals,indices,24,36);
	
	return mesh;
}

ModelMesh* RenderingManager::GeneratePrimitive(myth::phys::Rectangle rectangle)
{
	ModelMesh *mesh = new ModelMesh();
	Point points[] = {rectangle.m_pointA,rectangle.m_pointB,rectangle.m_pointC,rectangle.m_pointB+(rectangle.m_pointC-rectangle.m_pointA)};
	Normal rectNormal = glm::cross(rectangle.m_pointB-rectangle.m_pointA,rectangle.m_pointC-rectangle.m_pointA);
	Normal normals[] = {rectNormal,rectNormal,rectNormal,rectNormal};
	TexCoord texcoords[] = {TexCoord(0,0),TexCoord(1,0),TexCoord(0,1),TexCoord(1,1)};
	unsigned short indices[] = {0,1,2,1,2,3};

	mesh->Initialize(points,texcoords,normals,indices,4,6);
	
	return mesh;
}

ModelMesh* RenderingManager::GeneratePrimitive(Triangle triangle)
{
	Assert(0,"NOT IMPLEMENTED");
	return 0;
}

void RenderingManager::RenderPrimitive(AABB aabb)
{
	ModelMesh *m = GeneratePrimitive(aabb);
	m->Render();
	delete m;
}
void RenderingManager::RenderPrimitive(Line line)
{
	Assert(0,"NOT IMPLEMENTED");
}
void RenderingManager::RenderPrimitive(LineSegment lineSegment)
{
	Assert(0,"NOT IMPLEMENTED");
}
void RenderingManager::RenderPrimitive(OBB obb)
{
	Assert(0,"NOT IMPLEMENTED");
}
void RenderingManager::RenderPrimitive(Plane plane)
{
	phys::Point center = plane.m_normal * plane.m_odistance;

	ModelMesh mesh = ModelMesh();
	phys::Point points[] = {center + 100000.0f*plane.GetPlaneVectorA(),center+100000.0f*plane.GetPlaneVectorB()
		,center-100000.0f*plane.GetPlaneVectorA(),center-100000.0f*plane.GetPlaneVectorB()};
	unsigned short indices[] = {0,1,2,1,2,3};

	mesh.Initialize(points,indices,4,6);

	mesh.Render();
}
void RenderingManager::RenderPrimitive(Polyhedron polyhedron)
{
	Assert(0,"NOT IMPLEMENTED");
}

void RenderingManager::RenderPrimitive(PointCloud polygon)
{
	Assert(0,"NOT IMPLEMENTED");
}
void RenderingManager::RenderPrimitive(Point point)
{
	GLuint VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(Point),&point,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glDrawArrays(GL_POINTS,0,1);
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1,&VBO);
}
void RenderingManager::RenderPrimitive(myth::phys::Rectangle rectangle)
{
	ModelMesh mesh = ModelMesh();
	phys::Point points[] = {rectangle.m_pointA,rectangle.m_pointB,rectangle.m_pointC,rectangle.m_pointB+(rectangle.m_pointC-rectangle.m_pointA)};
	phys::Normal mnormal = glm::cross(rectangle.m_pointB-rectangle.m_pointA,rectangle.m_pointC-rectangle.m_pointA);
	phys::Normal normals[] = {mnormal,mnormal,mnormal,mnormal,mnormal};
	phys::TexCoord texcoords[] = {phys::TexCoord(0,0),phys::TexCoord(1,0),phys::TexCoord(0,1),phys::TexCoord(1,1)};
	unsigned short indices[] = {0,1,2,1,2,3};

	mesh.Initialize(points,texcoords,normals,indices,4,6);

	mesh.Render();
}

void RenderingManager::RenderPrimitive(Sphere sphere)
{
	Assert(0,"NOT IMPLEMENTED");
}

void RenderingManager::RenderPrimitive(Tetrahedron tetrahedron)
{
	ModelMesh mesh = ModelMesh();
	phys::Point points[] = {tetrahedron.m_pointA,tetrahedron.m_pointB,tetrahedron.m_pointC, tetrahedron.m_pointD};
	unsigned short indices[] = {0,1,2,1,2,3,0,1,3,0,2,3};

	mesh.Initialize(points,indices,4,12);

	mesh.Render();
}

void RenderingManager::RenderPrimitive(Triangle triangle)
{
	ModelMesh mesh = ModelMesh();
	phys::Point points[] = {triangle.m_pointA,triangle.m_pointB,triangle.m_pointC};
	phys::Normal mnormal = glm::cross(triangle.m_pointB-triangle.m_pointA,triangle.m_pointC-triangle.m_pointA);
	phys::Normal normals[] = {mnormal,mnormal,mnormal};
	phys::TexCoord texcoords[] = {phys::TexCoord(0,0),phys::TexCoord(1,0),phys::TexCoord(0,1)};
	unsigned short indices[] = {0,1,2};

	mesh.Initialize(points,texcoords,normals,indices,3,3);

	mesh.Render();
}