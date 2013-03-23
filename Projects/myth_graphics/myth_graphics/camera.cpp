
#include <myth\graphics\camera.h>

using namespace myth::graphics;
using namespace glm;

Camera::Camera()
{
	viewmatrix = mat4(1.0f);
	projection = mat4(1.0f);
	cameraPosition = vec3(0.0f);
	cameraDirection = vec3(0.0,0.0,1.0);
	cameraUp = vec3(0.0,1.0,0.0);
	pitch = 0;
	Update();
}

Camera::~Camera()
{
}

mat4 Camera::ProjectionMatrix() const
{
	return projection;
}
mat4 Camera::ViewMatrix() const
{
	return viewmatrix;
}
mat4 Camera::ViewProjectionMatrix() const
{
	return projection * viewmatrix;
}

void Camera::Update()
{
	viewmatrix = glm::lookAt(cameraPosition,cameraPosition + cameraDirection,cameraUp);
	viewprojection = viewmatrix * projection;
}

void Camera::Perspective(float fieldofview,float aspectratio,float znear,float zfar)
{
	projection = glm::perspective(fieldofview,aspectratio,znear,zfar);
	viewprojection = viewmatrix * projection;
}

void Camera::Yaw(float deg)
{
	cameraDirection = glm::rotate(cameraDirection,deg,cameraUp);
	Update();
}

void Camera::Pitch(float deg)
{
	if (abs(pitch+deg) > 60) return;
	pitch += deg;
	vec3 cross = glm::cross(cameraDirection,cameraUp);
	cameraDirection = glm::rotate(cameraDirection,deg,cross);
	Update();
}

void Camera::Roll(float deg)
{
	cameraUp = glm::rotate(cameraUp,deg,cameraDirection);
	Update();
}

void Camera::MoveForward(float amount)
{
	cameraPosition += cameraDirection * amount;
	Update();
}

void Camera::MoveSideways(float amount)
{
	cameraPosition += glm::normalize(glm::cross(cameraDirection,cameraUp)) * amount;
	Update();
}

void Camera::MoveUp(float amount)
{
	cameraPosition += cameraUp * amount;
	Update();
}

void Camera::SetPosition(vec3 position)
{
	cameraPosition = position;
	Update();
}
void Camera::SetDirection(vec3 direction)
{
	cameraDirection = direction;
	Update();
}
void Camera::SetUp(vec3 up)
{
	cameraUp = up;
	Update();
}