#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>
#include <iostream>

namespace scim
{
	namespace math
	{

	class Vector3 {
	public:
		F32 x,y,z;

		Vector3(const Vector3 &a);
		Vector3(float nx, float ny, float nz);

		// friend std::ostream& operator<<(std::ostream& os, const Vector3& s);

		Vector3 &operator =(const Vector3 &a) {
			x = a.x; y = a.y; z = a.z;
			return *this;
		}
		bool operator ==(const Vector3 &a) const {
			return x==a.x && y==a.y && z==a.z;
		}
		bool operator !=(const Vector3 &a) const {
			return x!=a.x || y!=a.y || z!=a.z;
		}
		Vector3 operator -() const {
			return Vector3(-x, -y, -z);
		}
		Vector3 operator +(const Vector3 &a) const {
			return Vector3(x + a.x, y + a.y, z + a.z);
		}
		Vector3 operator -(const Vector3 &a) const {
			return Vector3(x - a.x, y - a.y, z - a.z);
		}
		Vector3 operator *(float a) const {
			return Vector3(x*a, y*a, z*a);
		}
		Vector3 operator /(float a) const {
			float oneOverA = 1.0f / a; // NOTE: no check for divide by zero here
			return Vector3(x*oneOverA, y*oneOverA, z*oneOverA);
		}
		Vector3 &operator +=(const Vector3 &a) {
			x += a.x; y += a.y; z += a.z;
			return *this;
		}
		Vector3 &operator -=(const Vector3 &a) {
			x -= a.x; y -= a.y; z -= a.z;
			return *this;
		}
		Vector3 &operator *=(float a) {
			x *= a; y *= a; z *= a;
			return *this;
		}
		Vector3  &operator /=(float a) {
			float oneOverA = 1.0f / a;
			x *= oneOverA; y *= oneOverA; z *= oneOverA;
			return *this;
		}
		float operator *(const Vector3 &a) const { /* dot product */
			return x*a.x + y*a.y + z*a.z;
		}

		void normalize();
		void print();

		static float vectorMag(const Vector3 &a);
		static inline float distance(const Vector3 &a, const Vector3 &b);
	};

	inline Vector3 operator *(float k, const Vector3 &v) {
		return Vector3(k*v.x, k*v.y, k*v.z);
	}

	extern const Vector3 kZeroVector;

	}
}
#endif
