
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <myth\assets\asset.h>

namespace myth
{
	namespace graphics
	{
		class Texture;
		class ShaderProgram;
		class Camera;
		class ModelMesh;
		
		enum
		{
			SKYBOX_SPHERE = 1,
			SKYBOX_BOX    = 2
		};

		//! Class representing a skybox. The skybox consists of a cubemap that will be rendered around the specified camera.
		class declspec_graphics Skybox : public myth::assets::SourceAsset
		{
		public:
			//! Empty Constructor, creates an empty skybox with no texture, shader program or camera specified
			Skybox();
			//! Initialization constructor, initializes a skybox with asset data
			Skybox(myth::assets::AssetData *assetData, int package);
			//! Destructor
			~Skybox();
			
			float& Size() { return m_size;}
			void SetType(unsigned short type);

			void LoadFromSource(std::string source);
			void ReloadFromSource(std::string source);
			void Destroy();
			bool IsLoaded();

			void BindCamera(Camera* camera);

			void Render();
		private:
			Texture *m_texture;
			ShaderProgram *m_shaderProgram;
			ModelMesh *m_mesh;
			Camera *m_camera;
			float m_size;
			unsigned short m_type;
		};
	}
}