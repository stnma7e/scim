#include "Frustum.h"

namespace scim
{
	namespace math
	{

	Frustum::Frustum()
	{
		m_Fov = PI / 4.0f; // default FOV is 90 degrees
		m_AspectRatio = 1.0f;
		m_Near = 1.0f;
		m_Far = 1000.f;
	}

	bool Frustum::Inside(const Vec3& point) const
	{
		for (I8 i = 0; i < NUM_PLANES; ++i)
		{
			if (!m_Planes[i].Inside(point))
				return false;
		}

		return true;
	}
	bool Frustum::Inside(const Vec3& point, const F32 radius) const
	{
		for (I8 i = 0; i < NUM_PLANES; ++i)
		{
			if (!m_Planes[i].Inside(point, radius))
				return false;
		}

		// otherwise we are fully in view
		return true;
	}

	void Frustum::Init(const F32 fov, const F32 aspect, const F32 near, const F32 far)
	{
		/*
			m_Fov = fov;
			m_AspectRatio = aspect;
			m_Near = near;
			m_Far = far;

			F64 tanFovOver2 = tan(m_Fov / 2.0f)
			Vec3 nearRight = (m_Near * tanFovOver2) * m_AspectRatio * g_Right;
			Vec3 farRight  = (m_Far * tanFovOver2) * m_AspectRatio * g_Right;
			Vec3 nearUp    = (m_Near * tanFovOver2) * m_AspectRatio * g_Up;
			Vec3 farUp     = (m_Far * tanFovOver2) * m_AspectRatio * g_Up;

			// points start in upper right and go around clockwise
			m_NearClip[0] = (m_Near * g_Forward) - nearRight + nearUp;
			m_NearClip[1] = (m_Near * g_Forward) + nearRight + nearUp;
			m_NearClip[2] = (m_Near * g_Forward) + nearRight - nearUp;
			m_NearClip[3] = (m_Near * g_Forward) - nearRight + nearUp;

			m_FarClip[0] = (m_Far * g_Forward) - farRight + farUp;
			m_FarClip[1] = (m_Far * g_Forward) + farRight + farUp;
			m_FarClip[2] = (m_Far * g_Forward) + farRight - farUp;
			m_FarClip[3] = (m_Far * g_Forward) - farRight - farUp;

			Vec3 origin(0.0f, 0.0f, 0.0f);
			m_Planes[NEAR].Init(m_NearClip[2], m_NearClip[1], m_NearClip[0]);
			m_Planes[FAR].Init(m_FarClip[0], m_FarClip[1], m_FarClip[2]);
			m_Planes[RIGHT].Init(m_FarClip[2], m_FarClip[1], origin);
			m_Planes[TOP].Init(m_FarClip[1], m_FarClip[0], origin);
			m_Planes[LEFT].Init(m_FarClip[0], m_FarClip[3], origin);
			m_Planes[BOTTOM].Init(m_FarClip[3], m_FarClip[2], origin);
		*/
	}

	}
}
