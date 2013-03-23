
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

void RenderingManager::RenderPrimitive(AABB aabb)
{
}
void RenderingManager::RenderPrimitive(Line line)
{
}
void RenderingManager::RenderPrimitive(LineSegment lineSegment)
{
}
void RenderingManager::RenderPrimitive(OBB obb)
{
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
}

void RenderingManager::RenderPrimitive(PointCloud polygon)
{
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
void RenderingManager::RenderPrimitive(Rectangle rectangle)
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