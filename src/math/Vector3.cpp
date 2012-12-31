#include "Vector3.h"
#include <cmath>

namespace scim
{
	namespace math
	{
		Vector3::Vector3(const Vector3 &a) : x(a.x), y(a.y), z(a.z)
		{

		}
		Vector3::Vector3(F32 nx, F32 ny, F32 nz) : x(nx), y(ny), z(nz)
		{

		}
		void Vector3::normalize(void)
		{
			F32 magSq = x*x + y*y + z*z;
			if (magSq > 0.0f) {
				F32 oneOverMag = 1.0f / std::sqrt(magSq);
				x *= oneOverMag;
				y *= oneOverMag;
				z *= oneOverMag;
			}
		}
		inline F32 Vector3::distance(const Vector3 &a, const Vector3 &b)
		{
			F32 dx = a.x - b.x;
			F32 dy = a.y - b.y;
			F32 dz = a.z - b.z;
			return std::sqrt(dx*dx + dy*dy + dz*dz);
		}
		F32 Vector3::vectorMag(const Vector3 &a)
		{
			return std::sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
		}
		void Vector3::print()
		{
			std::cout << this->x << ", " << this->y << ", " << this->z << std::endl;
		}
	}
}
