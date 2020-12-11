#include "engpch.h"

#include "Transform.h"

#include "Engine/utils/QuaternionUtils.h"
#include <glm/ext/matrix_transform.hpp>

namespace Engine
{
	Transform::Transform()
		:m_Location(glm::vec3(0.0f)), m_Orientation(glm::quat(glm::vec3(0.0f))), m_Scale(glm::vec3(1.0f)), m_TransformMatrix(CalculateTransformMatrix())
	{}

	Transform::Transform(glm::vec3& location, glm::quat& orientation, glm::vec3& scale)
		: m_Location(location), m_Orientation(orientation), m_Scale(scale), m_TransformMatrix(CalculateTransformMatrix())
	{}


	/* Translation, Rotation, Scale */
	void Transform::SetLocation(const glm::vec3& location)
	{
		m_Location = location;
		m_TransformMatrix = CalculateTransformMatrix();
	}

	void Transform::SetOrientation(const glm::quat& orientation)
	{
		m_Orientation = orientation;
		m_TransformMatrix = CalculateTransformMatrix();
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		m_TransformMatrix = CalculateTransformMatrix();
	}

	void Transform::Translate(const float delta, const glm::vec3& axis)
	{
		SetLocation(m_Location + (delta * axis));
	}
	void Transform::Rotate(const float angle, const glm::vec3& axis)
	{
		SetOrientation(glm::angleAxis(glm::radians(angle), glm::normalize(axis)) * m_Orientation);
	}
	void Transform::Rotate(const glm::quat& quat)
	{
		SetOrientation(quat * m_Orientation);
	}
	void Transform::Scale(const float scale, const glm::vec3& axis)
	{
		SetScale(m_Scale * (scale * axis));
	}
	
	void Transform::LookAt(const glm::vec3& target)
	{
		SetOrientation(QuatLookAtTarget(m_Location, target, glm::vec3(0.0f, 1.0f, 0.0f)));	// TODO: replace with world up
	}


	/* Direction Vectors */
	// TODO: should direction vectors be stored as a private member?
	glm::vec3 Transform::GetFront() const
	{
		return m_Orientation * glm::vec3(0.0f, 0.0f, 1.0f);
	}

	glm::vec3 Transform::GetRight() const
	{
		return glm::normalize(glm::cross(GetFront(), glm::vec3(0.0f, 1.0f, 0.0f)));		// TODO: replace with world up
	}

	glm::vec3 Transform::GetUp() const
	{
		return glm::normalize(glm::cross(GetRight(), GetFront()));
	}


	/* Transform Matrix */
	const glm::mat4 Transform::CalculateTransformMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), m_Location) *
			glm::mat4_cast(m_Orientation) *
			glm::scale(glm::mat4(1.0f), m_Scale);
	}

}