#include "engpch.h"

#include "QuaternionUtils.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

namespace Engine
{

	glm::quat QuatLookAtTarget(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
	{
		glm::vec3 direction = position - target;
		float directionLength = glm::length(direction);

		// Check if the direction is valid; Also deals with NaN
		if (directionLength < 0.0001)
		{
			return glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // Just return identity
		}

		// Normalize direction
		direction = glm::normalize(direction);

		// Is the normal up (nearly) parallel to direction?
		if (glm::abs(glm::dot(direction, up)) > .9999f) 
		{
			// Use alternative up
			glm::vec3 alternativeUp = glm::vec3(0.0f, 0.0f, 1.0f);
			return glm::quatLookAt(direction, alternativeUp);
		}
		else 
		{
			return glm::quatLookAt(direction, up);
		}
	}

	glm::vec3 QuatToEulerAnglesRadians(const glm::quat& quat)
	{
		return glm::eulerAngles(quat);
	}

	glm::vec3 QuatToEulerAnglesDegrees(const glm::quat& quat)
	{
		return glm::degrees(QuatToEulerAnglesRadians(quat));
	}

	glm::quat EulerAnglesRadiansToQuat(const glm::vec3& rAngles)
	{
		return glm::quat(rAngles);
	}

	glm::quat EulerAnglesDegreesToQuat(const glm::vec3& dAngles)
	{
		return EulerAnglesRadiansToQuat(glm::radians(dAngles));
	}

}