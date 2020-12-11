#pragma once

#include "Camera.h"

namespace Engine
{

	class PerspectiveCamera : public Camera
	{

	public:

		PerspectiveCamera(float fov, float aspect, float zNear, float zFar);

		const float GetFOV() const { return m_FOV; }
		const float GetAspectRatio() const { return m_AspectRatio; }
		const float GetZNear() const { return m_ZNear; }
		const float GetZFar() const { return m_ZFar; }

		void SetFOV(const float fov);
		void SetAspectRatio(const float aspect);
		void SetZNear(const float zNear);
		void SetZFar(const float zFar);

		virtual void RecalculateProjectionMatrix() override;

	private:

		float m_FOV;
		float m_AspectRatio;
		float m_ZNear;
		float m_ZFar;

	};

}