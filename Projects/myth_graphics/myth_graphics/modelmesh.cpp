
#include <myth\debug\assert.h>
#include <myth\graphics\modelmesh.h>

using namespace myth::graphics;

ModelMesh::ModelMesh()
{
}

ModelMesh::~ModelMesh()
{
	Destroy();
}

void ModelMesh::Render()
{
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES,m_indexcount,GL_UNSIGNED_SHORT,0); 

	glBindVertexArray(0);
}

void ModelMesh::Initialize(void *position, unsigned int vertexcount)
{
	unsigned short *indices = new unsigned short[vertexcount];
	for(int i = 0; i < vertexcount; ++i) indices[i] = i;

	Initialize(position,indices,vertexcount,vertexcount);

	delete [] indices;
}


void ModelMesh::Initialize(void *position, unsigned short *indices, unsigned int vertexcount, unsigned int indexcount)
{
	m_indexcount = indexcount;

	GenerateBuffers();

	glBindVertexArray(VAO);

	InitializeVertexData(VBO[0], 0, position, vertexcount, 3);
	InitializeIndexData(IB, indices, indexcount, sizeof(unsigned short));

	glBindVertexArray(0);
}

void ModelMesh::Initialize(void* position, void *texcoord, void *normal, unsigned short *indices, unsigned int vertexcount,unsigned int indexcount)
{
	m_indexcount = indexcount;
	
	GenerateBuffers();

	glBindVertexArray(VAO);

	InitializeVertexData(VBO[0], 0, position, vertexcount, 3);
	InitializeVertexData(VBO[1], 1, texcoord, vertexcount, 2);
	InitializeVertexData(VBO[2], 2, normal  , vertexcount, 3);
	InitializeVertexData(VBO[3], 3, CalculateTangentVectors(position,texcoord,normal,indices,vertexcount,indexcount), vertexcount, 3);
	InitializeIndexData(IB, indices, indexcount, sizeof(unsigned short));

	glBindVertexArray(0);
}

void* ModelMesh::CalculateTangentVectors(void* position, void *texcoord, void *normal,unsigned short* indices, unsigned int vertexcount, unsigned int indexcount)
{
	glm::vec3 *tangentVectors = new glm::vec3[vertexcount];
	glm::vec3* vertices       = (glm::vec3*) position;
	glm::vec2* texcoords      = (glm::vec2*) texcoord;

	for (unsigned int i = 0 ; i < indexcount/3; i ++) 
	{
		glm::vec3& v0pos =  vertices[indices[i*3+0]];
		glm::vec3& v1pos =  vertices[indices[i*3+1]];
		glm::vec3& v2pos =  vertices[indices[i*3+2]];
		glm::vec2& v0tex = texcoords[indices[i*3+0]];
		glm::vec2& v1tex = texcoords[indices[i*3+1]];
		glm::vec2& v2tex = texcoords[indices[i*3+2]];

		glm::vec3 edge1 = v1pos - v0pos;
		glm::vec3 edge2 = v2pos - v0pos;

		float deltaU1 = v1tex.x - v0tex.x;
		float deltaV1 = v1tex.y - v0tex.y;
		float deltaU2 = v2tex.x - v0tex.x;
		float deltaV2 = v2tex.y - v0tex.y;

		float f = 1.0f / (deltaU1 * deltaV2 - deltaU2 * deltaV1);

		glm::vec3 tangent;

		tangent.x = f * (deltaV2 * edge1.x - deltaV1 * edge2.x);
		tangent.y = f * (deltaV2 * edge1.y - deltaV1 * edge2.y);
		tangent.z = f * (deltaV2 * edge1.z - deltaV1 * edge2.z);

		tangentVectors[indices[i*3+0]] += tangent;
		tangentVectors[indices[i*3+1]] += tangent;
		tangentVectors[indices[i*3+2]] += tangent;
	}

	for (unsigned int i = 0 ; i < vertexcount; i++) 
	{
		tangentVectors[i] = glm::normalize(tangentVectors[i]);
	}

	return tangentVectors;
}


void ModelMesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);

	glGenBuffers(4, VBO);
	glGenBuffers(1, &IB);
}

void ModelMesh::InitializeVertexData(GLuint VBO, int attribIndex, void *data, size_t amount, size_t individualSize)
{
	Assert(data, "MESH LOAD ERROR: Attempting to load a mesh with invalid vertex data (pointer to data is NULL)");

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float) * individualSize, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribIndex, individualSize, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribIndex);
}

void ModelMesh::InitializeIndexData(GLuint IB, void* indices, size_t amount, size_t typeSize)
{
	Assert(indices,"MESH LOAD ERROR: Attempting to load a mesh with invalid index data (pointer to data is NULL)");

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, typeSize * amount, indices, GL_STATIC_DRAW);
}

void ModelMesh::BindTexture(const Texture& texture, int index)
{
	glBindVertexArray(VAO);
	texture.Bind(index);
	glBindVertexArray(0);
}

void ModelMesh::Destroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(4, VBO);
	glDeleteBuffers(1, &IB);
}