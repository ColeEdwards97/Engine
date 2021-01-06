#pragma once

#include "Engine/SparseSet.h"
#include "Engine/Entity/IComponent.h"

namespace Engine
{

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

		Ref<T> GetComponent(const EntityID id)
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

	public:

		// ITERATOR
		using iterator = typename std::vector<Ref<T>>::iterator;
		using const_iterator = typename std::vector<Ref<T>>::const_iterator;
		using reverse_iterator = typename std::vector<Ref<T>>::reverse_iterator;
		using const_reverse_iterator = typename std::vector<Ref<T>>::const_reverse_iterator;

		iterator begin() { return m_Components.begin(); }
		iterator end() { return m_Components.end(); }
		const_iterator begin() const { return m_Components.begin(); }
		const_iterator end() const { return m_Components.end(); }
		reverse_iterator rbegin() { return m_Components.rbegin(); }
		reverse_iterator rend() { return m_Components.rend(); }
		const_reverse_iterator rbegin() const { return m_Components.rbegin(); }
		const_reverse_iterator rend() const { return m_Components.rend(); }


	private:
		
		SparseSet<EntityID, Ref<T>> m_Components;

	};

}