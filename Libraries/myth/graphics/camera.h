
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform2.hpp>
#include <gtx/rotate_vector.hpp>

namespace myth
{
	namespace graphics
	{
		class declspec_graphics Camera
		{
		public:
			Camera();
			~Camera();

			void Perspective(float fov,float aspect,float znear,float zfar);
			void Yaw(float degrees);
			void Pitch(float degrees);
			void Roll(float degrees);
			void MoveForward(float amount);
			void MoveSideways(float amount);
			void MoveUp(float amount);
			void SetPosition(glm::vec3 position);
			void SetDirection(glm::vec3 direction);
			void SetUp(glm::vec3 up);
			glm::mat4 ViewMatrix() const;
			glm::mat4 ProjectionMatrix() const;
			glm::mat4 ViewProjectionMatrix() const;

			glm::vec3 Position() const{return cameraPosition;}
			glm::vec3 Direction() const{return cameraDirection;}
			glm::vec3 Up() const{return cameraUp;}
		private:
			void Update();

			float pitch;

			glm::mat4 viewmatrix;
			glm::mat4 projection;
			glm::mat4 viewprojection;

			glm::vec3 cameraPosition;
			glm::vec3 cameraDirection;
			glm::vec3 cameraUp;
		};

	}
}