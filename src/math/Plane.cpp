#include "Plane.h"

namespace scim
{
	namespace math
	{

	void Plane::Normalize()
	{
		F32 mag;
		mag = std::sqrt((n.x * n.x) + (n.y * n.y) + (n.z * n.z));

		n.x = n.x / mag;
		n.y = n.y / mag;
		n.z = n.z / mag;
		d = d / mag;
	}
	inline void Plane::Init(const Vec3& p0, const Vec3& p1, const Vec3& p2)
	{
		n = Vec3(p1-p0).Cross(p2-p0).Normalized();
		d =- n.Dot(p0);
		Normalize();
	}

	bool Plane::Inside(const Vec3& point) const
	{
		F32 result = DotCoord(point);
		return (result >= 0.0f);
	}
	bool Plane::Inside(const Vec3& point, const F32 radius) const
	{
		F32 fDistance;

		fDistance = DotCoord(point);
		return (fDistance >= -radius);
	}

	}
}