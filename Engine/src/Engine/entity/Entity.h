#pragma once

#include "Engine/World/Transform.h"

namespace Engine
{
	class Entity
	{

	public:

		Entity() {}
		virtual ~Entity() {}
		
		virtual void OnUpdate() = 0;

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);

	private:
		
		uint64_t m_ID;
		Transform& m_Transform = Transform();

	};


}