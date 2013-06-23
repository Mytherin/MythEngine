
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif

#include <GL\glew.h>
#include <myth\graphics\texture.h>
#include <myth\graphics\vertex.h>

namespace myth
{
	namespace graphics
	{
		class declspec_graphics ModelMesh
		{
		public:
			//! Empty Constructor
			ModelMesh();
			//! Destructor
			~ModelMesh();

			//! Renders the mesh
			void Render();
			void Initialize(void *position, unsigned int vertexcount);
			void Initialize(void* position,unsigned short* indices, unsigned int vertexcount, unsigned int indexcount);
			//! Creates the mesh from the mesh data
			void Initialize(void* position, void *texcoord, void *normal,unsigned short* indices, unsigned int vertexcount, unsigned int indexcount);
			void BindTexture(const Texture& texture, int index);
			void GenerateBuffers();
			void InitializeVertexData(GLuint VBO, int attribIndex, void *data, size_t amount, size_t individualSize);
			void InitializeIndexData(GLuint IB, void* indices, size_t amount, size_t typeSize);
			
			//! Destroys the mesh
			void Destroy();
		private:
			//! Compute the tangent vector used for the normal map
			void* CalculateTangentVectors(void* position, void *texcoord, void *normal,unsigned short* indices, unsigned int vertexcount, unsigned int indexcount);

			GLuint VAO;
			GLuint VBO[4];
			GLuint IB;
			unsigned int m_indexcount;
		};

	}
}