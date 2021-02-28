#pragma once

#include <glm/glm.hpp>

namespace Engine
{



	class World
	{
	public:
		const glm::vec3 GetWorldUp() const { return m_WorldUp; }

	private:
		const glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };
	};


}