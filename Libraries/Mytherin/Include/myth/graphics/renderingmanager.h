
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif


#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <myth\phys\shapes.h>
#include <myth\graphics\mesh.h>


namespace myth
{
	namespace graphics
	{
		class declspec_graphics RenderingManager
		{
		public:
			ModelMesh* GeneratePrimitive(phys::AABB aabb);
			ModelMesh* GeneratePrimitive(phys::Rectangle rectangle);
			ModelMesh* GeneratePrimitive(phys::Triangle triangle);

			void RenderPrimitive(phys::AABB aabb);
			void RenderPrimitive(phys::Line line);
			void RenderPrimitive(phys::LineSegment lineSegment);
			void RenderPrimitive(phys::OBB obb);
			void RenderPrimitive(phys::Plane plane);
			void RenderPrimitive(phys::Polyhedron polyhedron);
			void RenderPrimitive(phys::PointCloud polygon);
			void RenderPrimitive(phys::Point point);
			void RenderPrimitive(phys::Rectangle rectangle);
			void RenderPrimitive(phys::Sphere sphere);
			void RenderPrimitive(phys::Tetrahedron tetrahedron);
			void RenderPrimitive(phys::Triangle triangle);

			static RenderingManager& Instance()
			{
				static RenderingManager* m_instance = new RenderingManager;
				return *m_instance;
			}
		private:
			RenderingManager();
			~RenderingManager();
		};

#define g_renderingManager myth::graphics::RenderingManager::Instance()
	}
}