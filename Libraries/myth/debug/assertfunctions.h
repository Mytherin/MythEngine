
//A library of functions used by assertions, these will get turned into functions inline functions always returning true in release mode, completely compiling them out

#pragma once

#ifdef _DEBUG

#include <glm.hpp>
#include <gtx\norm.hpp>


inline bool NotNull(const glm::vec3& A)
{
	return A.x != 0 && A.y != 0 && A.z != 0;
}

inline bool IsNormal(const glm::vec3& A)
{
	return (glm::length2(A) > 0.999 && glm::length2(A) < 1.001);
}

//! Returns whether or not two points are inequal
inline bool AreInequal(const glm::vec3& A, const glm::vec3& B)
{
	return A != B;
}

//! Returns whether or not two points are inequal
inline bool AreInequal(const glm::vec3& A, const glm::vec3& B,const glm::vec3& C)
{
	return A != B && B != C && A != C;
}

//! Returns whether or not two points are inequal
inline bool AreInequal(const glm::vec3& A, const glm::vec3& B,const glm::vec3& C,const glm::vec3& D)
{
	return A != B && B != C && A != C && A != D && B != D && C != D;
}


//! Returns whether or not three points are not collinear
inline bool AreNotCollinear(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C)
{
	glm::vec3 line = B - A;

	float t = glm::dot(line,C-A) / glm::length2(line);

	return (A + line * t != C);
}

//! Returns whether or not four points are not collinear
inline bool AreNotCollinear(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D)
{
	if (!AreNotCollinear(A,B,C)) 
		return false;
	if (!AreNotCollinear(A,B,D)) 
		return false;
	if (!AreNotCollinear(A,C,D)) 
		return false;
	if (!AreNotCollinear(B,C,D)) 
		return false;

	return true;
}

//! Returns whether or not four points are not coplanar
inline bool AreNotCoplanar(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D)
{
	glm::vec3 normal = glm::normalize(glm::cross(B - A, C - A));

	glm::vec3 toPoint = D - A;
	float dist = glm::dot(normal,toPoint);

	return dist != 0;
}

#else

inline bool IsNormal(const glm::vec3& A)
{
	return true;
}

inline bool NotNull(const glm::vec3& A)
{
	return true;
}

inline bool AreInequal(const glm::vec3& A, const glm::vec3& B)
{
	return true;
}

inline bool AreInequal(const glm::vec3& A, const glm::vec3& B,const glm::vec3& C)
{
	return true;
}

inline bool AreInequal(const glm::vec3& A, const glm::vec3& B,const glm::vec3& C,const glm::vec3& D)
{
	return true;
}


inline bool AreNotCollinear(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C)
{
	return true;
}

inline bool AreNotCollinear(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D)
{
	return true;
}

inline bool AreNotCoplanar(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D)
{
	return true;
}

#endif