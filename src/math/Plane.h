#ifndef PLANE_H_
#define PLANE_H_

#include "Vec3.h"

namespace scim
{
	namespace math
	{

	class Plane
	{
	public:
		Vec3 n;
		F32 d;

		Plane() : d(0)
		{
		}
		//normal/offset form
		Plane(F32 a, F32 b, F32 c, F32, F32 d) : d(d)
		{
			const Vec3 m(a, b, c);
			n = m;
		}
		Plane(const Vec3 &n, float d) : n(n), d(d)
		{
		}
		//point/normal form
		Plane(const Vec3 &p, const Vec3 &n) : n(n), d(-n.Dot(p))
		{
		}
		//create plane from tri
		Plane(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2)
		{
			n = Vec3(v1-v0).Cross(v2-v0).Normalized();
			d =- n.Dot(v0);
		}
		Plane operator-() const
		{
			return Plane( -n,-d );
		}
		/*
			float t_Intersect(const Line &q) const
			{
				return -Distance(q.o) / n.Dot(q.d);
			}
			Vec3 Intersect(const Line &q) const
			{
				return q * t_Intersect(q);
			}
			Line Intersect(const Plane &q) const
			{
				Vec3 lv=n.Cross(q.n).Normalized();
				return Line(q.Intersect(Line(Nearest(n * -d), n.Cross(lv))), lv);
			}
		*/
		Vec3 Nearest(const Vec3 &q) const
		{
			return q-n * Distance(q);
		}
		void Negate()
		{
			n = -n;
			d = -d;
		}
		F32 Distance(const Vec3 &q) const
		{
			return n.Dot(q)+d;
		}
		inline F32 DotCoord(const Vec3& point) const
		{
			return ((n.x * point.x) + (n.y * point.y) + (n.z + point.z) + (d * 1));
		}

		inline void Normalize();
		inline void Init(const Vec3& p0, const Vec3& p1, const Vec3& p2);

		bool Inside(const Vec3& point, const F32 radius) const;
		bool Inside(const Vec3& point) const;
	};

	}
}

#endif