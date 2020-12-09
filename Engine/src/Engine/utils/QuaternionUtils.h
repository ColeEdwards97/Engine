#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	glm::vec3 LookAtTarget(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
	glm::vec3 QuatToEulerAnglesRadians(const glm::quat& quat);
	glm::vec3 QuatToEulerAnglesDegrees(const glm::quat& quat);
}