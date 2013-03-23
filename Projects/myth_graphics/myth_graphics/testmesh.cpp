//
//#include <myth\debug\assert.h>
//#include <myth\graphics\testmesh.h>
//
//using namespace myth::graphics;
//
//ModelMesh::ModelMesh()
//{
//}
//
//ModelMesh::~ModelMesh()
//{
//	Destroy();
//}
//
//void ModelMesh::Render()
//{
//	glBindVertexArray(VAO);
//
//	glDrawElements(GL_TRIANGLES,m_indexcount,GL_UNSIGNED_SHORT,0); 
//
//	glBindVertexArray(0);
//}
//
//void ModelMesh::Initialize(void *position, unsigned int vertexcount)
//{
//	unsigned short *indices = new unsigned short[vertexcount];
//	for(int i = 0; i < vertexcount; ++i) indices[i] = i;
//
//	Initialize(position,indices,vertexcount,vertexcount);
//
//	delete [] indices;
//}
//
//
//void ModelMesh::Initialize(void *position, unsigned short *indices, unsigned int vertexcount, unsigned int indexcount)
//{
//	m_indexcount = indexcount;
//
//	GenerateBuffers();
//
//	glBindVertexArray(VAO);
//
//	InitializeVertexData(VBO[0],0,position,vertexcount,3);
//	InitializeIndexData(IB,indices,indexcount,sizeof(unsigned short));
//
//	glBindVertexArray(0);
//}
//
//void ModelMesh::Initialize(void* position, void *texcoord, void *normal, unsigned short *indices, unsigned int vertexcount,unsigned int indexcount)
//{
//	m_indexcount = indexcount;
//	
//	GenerateBuffers();
//
//	glBindVertexArray(VAO);
//
//	InitializeVertexData(VBO[0],0,position,vertexcount,3);
//	InitializeVertexData(VBO[1],1,texcoord,vertexcount,2);
//	InitializeVertexData(VBO[2],2,normal,vertexcount,3);
//	InitializeIndexData(IB,indices,indexcount,sizeof(unsigned short));
//
//	glBindVertexArray(0);
//}
//
//void ModelMesh::GenerateBuffers()
//{
//	glGenVertexArrays(1,&VAO);
//
//	glGenBuffers(3,VBO);
//	glGenBuffers(1,&IB);
//
//}
//
//void ModelMesh::InitializeVertexData(GLuint VBO, int attribIndex, void *data, size_t amount, size_t individualSize)
//{
//	Assert(data,"MESH LOAD ERROR: Attempting to load a mesh with invalid vertex data (pointer to data is NULL)");
//
//	glBindBuffer(GL_ARRAY_BUFFER,VBO);
//	glBufferData(GL_ARRAY_BUFFER,amount * sizeof(float) * individualSize,data,GL_STATIC_DRAW);
//	glVertexAttribPointer(attribIndex,individualSize,GL_FLOAT,GL_FALSE,0,0);
//	glEnableVertexAttribArray(attribIndex);
//}
//
//void ModelMesh::InitializeIndexData(GLuint IB, void* indices, size_t amount, size_t typeSize)
//{
//	Assert(indices,"MESH LOAD ERROR: Attempting to load a mesh with invalid index data (pointer to data is NULL)");
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IB);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER,typeSize * amount,indices,GL_STATIC_DRAW);
//}
//
//void ModelMesh::BindTexture(const Texture& texture, GLenum textureNumber)
//{
//	glBindVertexArray(VAO);
//	texture.Bind(textureNumber);
//	glBindVertexArray(0);
//}
//
//void ModelMesh::Destroy()
//{
//	glDeleteVertexArrays(1,&VAO);
//	glDeleteBuffers(3,VBO);
//	glDeleteBuffers(1,&IB);
//}