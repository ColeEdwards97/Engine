#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Engine
{

	class Transform
	{

	public:

		// TODO: take in world or scene
		Transform();
		Transform(const glm::vec3& location, const glm::quat& orientation, const glm::vec3& scale);
		~Transform() {}

		const glm::vec3& GetLocation() const { return m_Location; }
		const glm::quat& GetOrientation() const { return m_Orientation; }
		const glm::vec3& GetScale() const { return m_Scale; }

		glm::vec3 GetEulerAngles() const { return glm::eulerAngles(m_Orientation); }
		float GetPitch() const { return glm::pitch(m_Orientation); }
		float GetYaw() const { return glm::yaw(m_Orientation); }
		float GetRoll() const { return glm::roll(m_Orientation); }

		void SetLocation(const glm::vec3& location);
		void SetOrientation(const glm::quat& rotation);
		void SetScale(const glm::vec3& scale);

		void Translate(const float delta, const glm::vec3& axis);
		void Rotate(const float angle, const glm::vec3& axis);
		void Rotate(const glm::quat& quat);
		void Scale(const float scale, const glm::vec3& axis);

		void LookAt(const glm::vec3& target);

		const glm::mat4& GetTransformMatrix() const { return m_TransformMatrix; }

		glm::vec3 GetFront() const;
		glm::vec3 GetBack() const { return -1.0f * GetFront(); }
		glm::vec3 GetRight() const;
		glm::vec3 GetLeft() const { return -1.0f * GetRight(); }
		glm::vec3 GetUp() const;
		glm::vec3 GetDown() const { return -1.0f * GetUp(); }


	private:

		glm::vec3 m_Location;
		glm::quat m_Orientation;
		glm::vec3 m_Scale;

		glm::mat4 m_TransformMatrix;

	private:

		const glm::mat4 CalculateTransformMatrix() const;
		
	};

}