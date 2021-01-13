#pragma once

#include <glm/glm.hpp>

namespace Engine
{

	class Light
	{
	public:

		Light()
			: Position(glm::vec3(0.0f)), Diffuse(glm::vec3(0.0f))
		{}
		Light(const glm::vec3& position, const glm::vec3& diffuse)
			: Position(position), Diffuse(diffuse)
		{}
		
		glm::vec3 Position;
		glm::vec3 Diffuse;
	};

}