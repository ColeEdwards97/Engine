#pragma once

#include <glm/glm.hpp>

namespace Engine
{

	class Material
	{
	public:
	private:
		glm::vec4 m_Ambient;
		glm::vec4 m_Diffuse;
		glm::vec4 m_Emissive;
		glm::vec4 m_Specular;
		float m_Shininess;
	};

}