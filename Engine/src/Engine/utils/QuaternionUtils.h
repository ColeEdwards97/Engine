#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	glm::quat QuatLookAtTarget(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
	glm::vec3 QuatToEulerAnglesRadians(const glm::quat& quat);
	glm::vec3 QuatToEulerAnglesDegrees(const glm::quat& quat);
	glm::quat EulerAnglesRadiansToQuat(const glm::vec3& rAngles);
	glm::quat EulerAnglesDegreesToQuat(const glm::vec3& dAngles);
}