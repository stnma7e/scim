#include "Vec3.h"
#include <cmath>

namespace scim
{
	namespace math
	{
		const Vec3 kZeroVec(0,0,0);


		Vec3::Vec3() : glm::vec3(0.0f, 0.0f, 0.0f)
		{
		}
		Vec3::Vec3(const Vec3 &a) : glm::vec3(a.x, a.y, a.z)
		{
		}
		Vec3::Vec3(F32 nx, F32 ny, F32 nz) : glm::vec3(nx, ny, nz)
		{
		}
		Vec3 Vec3::Normalized()
		{
			F32 magSq = x*x + y*y + z*z;
			F32 oneOverMag;
			if (magSq > 0.0f)
			{
				oneOverMag = 1.0f / std::sqrt(magSq);
			}
			return Vec3(x * oneOverMag, y * oneOverMag, z * oneOverMag);
		}
		inline F32 Vec3::Distance(const Vec3 &a, const Vec3 &b)
		{
			F32 dx = a.x - b.x;
			F32 dy = a.y - b.y;
			F32 dz = a.z - b.z;
			return std::sqrt(dx*dx + dy*dy + dz*dz);
		}
		F32 Vec3::Mag(const Vec3 &a)
		{
			return std::sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
		}
	}
}
