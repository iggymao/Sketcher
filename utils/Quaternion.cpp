#include "stdafx.h"
#include <math.h>

#include "../utils/Quaternion.h"

Quaternion::Quaternion()
	: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{

}

Quaternion::~Quaternion()
{

}

void Quaternion::CreateFromAxisAngle(const float &in_x, const float &in_y, const float &in_z, const float &in_degrees)
{
	float angle = float((in_degrees / 180.0f) * PI);
	float result = float(sin(angle/2.0f));
	w = float(cos(angle/2.0f));

	// Calculate the x, y, and z of the quaternion
	x = float(in_x * result);
	y = float(in_y * result);
	z = float(in_z * result);
}

void Quaternion::CreateMatrix(float *pMatrix)
{
	if(pMatrix)
	{
		//First row
		pMatrix[0] = 1.0f - 2.0f * (y * y + z * z);
		pMatrix[1] = 2.0f * (x * y - w * z);
		pMatrix[2] = 2.0f * (x * z + w * y);
		pMatrix[3] = 0.0f;

		//Second row
		pMatrix[4] = 2.0f * (x * y + w * z);
		pMatrix[5] = 1.0f - 2.0f * (x * x + z * z);
		pMatrix[6] = 2.0f * (y * z - w * x);
		pMatrix[7] = 0.0f;

		//Third row
		pMatrix[8] = 2.0f * (x * z - w * y);
		pMatrix[9] = 2.0f * (y * z + w * x);
		pMatrix[10] = 1.0f - 2.0f * (x * x + y * y);
		pMatrix[11] = 0.0f;

		// Fourth row
		pMatrix[12] = 0.0f;
		pMatrix[13] = 0.0f;
		pMatrix[14] = 0.0f;
		pMatrix[15] = 1.0f;
	}
}

Quaternion Quaternion::operator *(const Quaternion &q)
{
	Quaternion r;

	r.w = w*q.w - x*q.x - y*q.y - z*q.z;
	r.x = w*q.x + x*q.w + y*q.z - z*q.y;
	r.y = w*q.y + y*q.w + z*q.x - z*q.z;
	r.z = w*q.z + z*q.w + x*q.y - y*q.x;

	return r;
}

//////////////////////////////////////////////////
//  Implementation for a general quaternion class
//////////////////////////////////////////////////

/*
#include "../utils/Quaternion.h"

// Quaternion
// - default constructor
// - creates a new quaternion with all parts equal to zero
template<class _Tp>
Quaternion<_Tp>::Quaternion(void)
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

// Quaternion
// - constructor
// - parameters : x. y, z, w, of elements of the quaternion
// - creates a new quaternion based on the elements passed in 
template<class _Tp>
Quaternion<_Tp>::Quaternion(_Tp wi, _Tp xi, _Tp yi, _Tp zi)
{
	w = wi;
	x = xi;
	y = yi;
	z = zi;
}

// Quaternion
// - constructor
// - parameters : vector/array of four elements
// - creates a new quaternion based on the elements passed in
template<class _Tp>
Quaternion<_Tp>::Quaternion(_Tp v[4])
{
	w = v[0];
	x = v[1];
	y = v[2];
	z = v[3];
}

// Quaterion
// - copy constructor
// - papraemters : const quaternion q
// - creates a new quaternion based on the quaternion passed in
template<class _Tp>
Quaternion<_Tp>:: Quaternion(const Quaternion<_Tp>& q)
{
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
}

// Quaternion
// - constructor
// - parameters : yaw, pitch, and roll of an Euler angle
// - creates a new quaternion based on the Euler elements passed in
template<class _Tp>
Quaternion<_Tp>::Quaternion(_Tp e[3], int order)
{
	EulerAngles ea;
	ea.x = e[0];
	ea.y = e[1];
	ea.z = e[2];
	ea.w = order;

	Quat q = Eul_ToQuat(ea);

	x = q.x;
	y = q.y;
	z = q.z;
	w = q.e;
}

// ~Quaternion
// - destructor
// - deleted dynamically allocated memory
template<class _Tp>
Quaternion<_Tp>::~Quaternion()
{
}
*/