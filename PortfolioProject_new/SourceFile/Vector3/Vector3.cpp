#include "Vector3.h"

Vector3::Vector3(const Vector3& a)
{
	x = a.x;
	y = a.y;
	z = a.z;
}

Vector3::Vector3(float nx, float ny, float nz)
{
	x = nx;
	y = ny;
	z = nz;
}
