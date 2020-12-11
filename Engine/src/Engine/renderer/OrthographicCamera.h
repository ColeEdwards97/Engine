#pragma once

#include "Camera.h"

namespace Engine
{

	class OrthographicCamera : public Camera
	{

	public:

		OrthographicCamera(float left, float right, float bottom, float top, float zNear = 0.1f, float zFar = 1.0f, float zoom = 1.0f);
		OrthographicCamera(float aspect, float zNear = 0.1f, float zFar = 1.0f, float zoom = 1.0f);
		
		virtual void RecalculateProjectionMatrix() override;

		const float GetZoom() const { return m_Zoom; }
		const float GetAspectRatio() const { return m_AspectRatio; }
		const float GetZNear() const { return m_ZNear; }
		const float GetZFar() const { return m_ZFar; }

		void SetZoom(const float zoom);
		void SetAspectRatio(const float aspect);
		void SetZNear(const float zNear);
		void SetZFar(const float zFar);

	private:

		float m_Zoom;
		float m_AspectRatio;
		float m_ZNear;
		float m_ZFar;

	};

}