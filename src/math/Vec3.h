#ifndef VEC3_H_
#define VEC3_H_

#include <cmath>
#include <iostream>

#include <glm/glm.hpp>

namespace scim
{
	namespace math
	{

	class Vec3: public glm::vec3
	{
	public:
		F32 x,y,z;

		Vec3();
		Vec3(const Vec3 &a);
		Vec3(F32 nx, F32 ny, F32 nz);
		Vec3(glm::vec3 vec) : x(vec.x), y(vec.y), z(vec.z) // probably inefficient; should check 
		{
		}

		Vec3 Normalized();

		Vec3 Cross(const Vec3& q) const
		{
			return Vec3((y * q.z) - (z * q.y), (z * q.x) - (x * q.z), (x * q.y) - (y * q.x));
		}
		F32 Dot(const Vec3& q) const
		{
			return x * q.x + y * q.y + z * q.z;
		}

		static F32 Mag(const Vec3& a);
		static inline F32 Distance(const Vec3 &a, const Vec3 &b);
	};


	inline Vec3 operator *(F32 k, const Vec3 &v) {
		return Vec3(k*v.x, k*v.y, k*v.z);
	}

	extern const Vec3 kZeroVec;

	}
}
#endif
