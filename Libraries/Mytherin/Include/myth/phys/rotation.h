
#pragma once

#include <glm.hpp>
#include <gtc\quaternion.hpp>

#define Quat2Mat glm::mat3_cast
#define Mat2Quat glm::quat_cast

namespace myth
{
	namespace phys
	{
		//! Unit Rotation in one dimension
		typedef glm::vec3 AxisRotation;
		//! 3x3 Rotation Matrix
		typedef glm::mat3 RotationMatrix;
		//! Quaternion
		typedef glm::quat Quaternion;

		//! Object that represents a rotation in three dimensional space
		struct __declspec(dllexport) Rotation
		{
		public:
			//! Default Constructor, initializes an identity matrix
			Rotation();

			//! Quaternion Constructor, creates a rotation from a quaternion
			Rotation(const Quaternion& quaternion);

			//! Matrix Constructor, creates a rotation from a rotation matrix
			Rotation(const RotationMatrix& rotationmatrix);
			
			//Creates the rotation from a Quaternion
			void Create(const Quaternion& quat);
			//Creates the rotation from a RotationMatrix
			void Create(const RotationMatrix& rot);

			AxisRotation operator[](int i) const;

			//! Converts the rotation object to a matrix
			RotationMatrix AsMatrix() const;
		private:
			AxisRotation X;
			AxisRotation Y;
		};
	}
}