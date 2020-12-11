#include "engpch.h"
#include "Math.h"

namespace Engine
{

	glm::vec3 ScreenToWorld(const glm::mat4& projectionViewMatrix, const glm::vec2& mousePosition, const glm::vec2& screenDimensions)
	{
		// https://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords

		// Map mouse position to [-1 : 1]
		glm::vec2 mousePositionMapped = Map(mousePosition, glm::vec2(0.0f), screenDimensions, glm::vec2(-1.0f), glm::vec2(1.0f));

		glm::min(mousePosition, screenDimensions);

		// Construct vector 4
		glm::vec4 screenSpace;
		screenSpace.x = mousePositionMapped.x;
		screenSpace.y = -mousePositionMapped.y;
		screenSpace.z = 0.0f;		// for OpenGL this is [-1 : 1] // for DirectX this is [0 : 1]
		screenSpace.w = 1.0f;

		// Calculate world space
		glm::vec4 worldSpace = screenSpace * glm::inverse(projectionViewMatrix);

		// Perspective Division
		worldSpace.w = 1.0f / worldSpace.w;
		worldSpace.x *= worldSpace.w;
		worldSpace.y *= worldSpace.w;
		worldSpace.z *= worldSpace.w;

		return glm::vec3(worldSpace.x, worldSpace.y, worldSpace.z);

	}

}