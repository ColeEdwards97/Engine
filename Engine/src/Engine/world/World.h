#pragma once

#include "Engine/ECS/Registry.h"

#include <glm/glm.hpp>

namespace Engine
{



	class World
	{
	public:


		[[nodiscard]] EntityID CreateEntity();

		template<typename Prototype, typename ... Args>
		[[nodiscard]] EntityID CreateEntity(Args&& ... args) {
			const EntityID id = m_Registry.Create();
			m_Registry.AddComponents(id, typename Prototype::type{}, std::forward<Args>(args)...);
			return id;
		}


		const glm::vec3 GetWorldUp() const { return m_WorldUp; }
		const Registry& GetRegistry() const { return m_Registry; }

	private:
		const glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };
		Registry m_Registry;

	};


}