#ifndef FRUSTUM_H_
#define FRUSTUM_H_

#include "Plane.h"
#include "Vec3.h"

namespace scim
{
	namespace math
	{

	class Frustum
	{
		enum Side
		{ 
			NEAR,
			FAR,
			TOP,
			BOTTOM,
			LEFT,
			RIGHT,

			NUM_PLANES
		};
		Plane m_Planes[NUM_PLANES];

		Vec3 m_NearClip[4];
		Vec3 m_FarClip[4];

		F32 m_Fov;
		F32 m_AspectRatio;
		F32 m_Near;
		F32 m_Far;
		F32 m_Scale; // INTEGRATE THIS
	public:
		Frustum();

		bool Inside(const Vec3& point) const;
		bool Inside(const Vec3& point, const F32 radius) const;

		const Plane& Get(Side side) { return m_Planes[side]; }

		void SetFOV(F32 fov)
		{
			m_Fov = fov;
			// Init(m_Fov, m_AspectRatio, m_Near, m_Far);
		}
		void SetAspectRatio(F32 aspect)
		{
			m_AspectRatio = aspect;
			// Init(m_Fov, m_AspectRatio, m_Near, m_Far);
		}
		void SetNear(F32 near)
		{
			m_Near = near;
			// Init(m_Fov, m_AspectRatio, m_Near, m_Far);
		}
		void SetFar(F32 far)
		{
			m_Far = far;
			// Init(m_Fov, m_AspectRatio, m_Near, m_Far);
		}
		void SetScale(F32 scale)
		{
			m_Scale = scale;
		}

		F32 GetFOV() { return m_Fov; }
		F32 GetAspectRatio() { return m_AspectRatio; }
		F32 GetNear() { return m_Near; }
		F32 GetFar() { return m_Far; }
		F32 GetScale() { return m_Scale; }

		void Init(const F32 fov, const F32 aspect, const F32 near, const F32 far);
	};

	}
}

#endif