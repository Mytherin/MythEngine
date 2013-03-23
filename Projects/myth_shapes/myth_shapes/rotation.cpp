
#include <myth\debug\assert.h>
#include <myth\debug\assertfunctions.h>
#include <myth\phys\shapes.h>
#include <myth\phys\rotation.h>

using namespace myth::phys;

Rotation::Rotation() 
	: X(AxisRotation(1,0,0)),Y(AxisRotation(0,1,0))
{
}

Rotation::Rotation(const Quaternion& quaternion)
{
	Create(quaternion);
}

Rotation::Rotation(const RotationMatrix& rotationmatrix)
{
	Create(rotationmatrix);
}

void Rotation::Create(const Quaternion& quat)
{
	Create(Quat2Mat(quat));
}

void Rotation::Create(const RotationMatrix& rot)
{
	X = AxisRotation(rot[0]);
	Y = AxisRotation(rot[1]);
	
	Assert(IsNormal(X),L"DEGENERATE ROTATION: Attempting to initialize a rotation with a non-unit vector X");
	Assert(IsNormal(Y),L"DEGENERATE ROTATION: Attempting to initialize a rotation with a non-unit vector Y");
}

RotationMatrix Rotation::AsMatrix() const
{
	AxisRotation Z = mCross(X,Y);
	return RotationMatrix(X[0],X[1],X[2],Y[0],Y[1],Y[2],Z[0],Z[1],Z[2]);
}

AxisRotation Rotation::operator[](int i) const
{
	if (i == 0) return X;
	if (i == 1) return Y;
	if (i == 2) return mCross(X,Y);

	Assert(false,L"INVALID ARGUMENT ERROR: Rotations only contains three vertices [0,1,2].");
	return X;
}