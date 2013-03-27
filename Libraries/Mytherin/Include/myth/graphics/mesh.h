
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif

#include <assimp\Importer.hpp>    
#include <assimp\scene.h>      
#include <assimp\postprocess.h> 

#include <myth\assets\asset.h>
#include <myth\graphics\material.h>
#include <myth\graphics\modelmesh.h>
#include <myth\graphics\shaderprogram.h>
#include <myth\graphics\texture.h>
#include <myth\graphics\vertex.h>

namespace myth
{
	namespace graphics
	{
		class declspec_graphics Mesh : public myth::assets::FileAsset
		{
		public:
			Mesh(myth::assets::FilePath *assetData, int package);

			~Mesh();
			
			virtual void LoadFromFile(std::string filepath);
			virtual void ReloadFromFile(std::string filepath);
			virtual void Destroy();
			virtual bool IsLoaded();

			void Render(ShaderProgram& program);

			//! Temp [testing purposes]
			void SetMaterial(Material material)
			{
				m_materials[0] = material;
			}
			//! Temp
			void LoadTexture(Texture& texture)
			{
				m_meshes[0].BindTexture(texture,0);
			}
		private:
			bool InitFromScene(const aiScene* pScene, const std::string& Filename);
			void InitMesh(unsigned int Index, const aiMesh* paiMesh);
			bool InitMaterials(const aiScene* pScene, const std::string& Filename);

			unsigned int m_meshCount;
			unsigned int m_materialCount;

			Texture *m_textures;
			ModelMesh *m_meshes;
			Material *m_materials;
		};
	}
}