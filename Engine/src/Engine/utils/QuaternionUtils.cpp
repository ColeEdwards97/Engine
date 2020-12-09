#include "engpch.h"

#include "QuaternionUtils.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

namespace Engine
{

	glm::vec3 LookAtTarget(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
	{
		return QuatToEulerAnglesDegrees(glm::conjugate(glm::toQuat(glm::lookAt(position, target, up))));
	}

	glm::vec3 QuatToEulerAnglesRadians(const glm::quat& quat)
	{
		return glm::eulerAngles(quat);
	}

	glm::vec3 QuatToEulerAnglesDegrees(const glm::quat& quat)
	{
		return glm::degrees(QuatToEulerAnglesRadians(quat));
	}

}