#pragma once

#include "Engine/SparseSet.h"
#include "Engine/Entity/IComponent.h"

namespace Engine
{

	using EntityID = uint32_t;

	// ComponentContainer Interface so an unordered map can be stored in the component manager
	class IComponentContainer
	{
	public:
		
		virtual ~IComponentContainer() = default;
		virtual void EntityDestroyed(const EntityID id) = 0;

	};

	// ComponentContainer Templated Class. Allows us to create a new SparseSet for every type of Component
	// Basically a SparseSet wrapper
	template<typename T>
	class ComponentContainer : public IComponentContainer
	{

	public:

		void AddComponent(const EntityID id, Ref<T> component)
		{
			m_Components.Insert(id, component);
		}

		Ref<T>& GetComponent(const EntityID id)
		{
			return m_Components.Get(id);
		}

		void RemoveComponent(const EntityID id)
		{
			m_Components.Erase(id);
		}

		virtual void EntityDestroyed(const EntityID id) override
		{
			RemoveComponent(id);
		}

	private:
		
		SparseSet<EntityID, Ref<T>> m_Components;

	};

}