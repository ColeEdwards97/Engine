#pragma once

#include "Engine/Core/Core.h"

#include "Engine/SparseSet.h"
#include "Engine/Entity/ComponentContainer.h"

#include "Engine/Event/Observer.h"
#include "Engine/Event/EntityEvent.h"

#include "Engine/Utils/FamilyTypeID.h"

namespace Engine
{

	class ComponentManager : public Observer
	{

	public:

		// STATIC ACCESSOR
		static ComponentManager& Get() { return *s_Instance; }
		
		template<typename T>
		Ref<ComponentContainer<T>> GetComponents()
		{
			return GetComponentContainer<T>();
		}

		// REGISTRY
		// TODO: should we have to do this?
		template<typename T>
		void RegisterComponentType()
		{
			Register<T>();
		}

		// OPERATIONS

		template<typename T, typename ... Args>
		void AddComponent(const EntityID id, Args&& ... args)
		{
			if (!IsRegistered<T>())
			{
				Register<T>();
			}
			GetComponentContainer<T>()->AddComponent(id, CreateRef<T>(std::forward<Args>(args)...));
		}

		template<typename T>
		Ref<T> GetComponent(const EntityID id)
		{
			return GetComponentContainer<T>()->GetComponent(id);
		}

		template<typename T>
		void RemoveComponent(const EntityID id)
		{
			GetComponentContainer<T>()->RemoveComponent(id);
		}


	private:

		static ComponentManager* s_Instance;

		// we are storing a map of ComponentTypeIDs -> Refs of IComponentContainers
		// ComponentContainers store SparseMaps of EntityIDs -> Refs of IComponents
		std::unordered_map<ComponentTypeID, Ref<IComponentContainer>> m_Components;


	private:

		// EVENT
		void OnEvent(Event& e)
		{
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<EntityDestroyedEvent>(ENG_BIND_EVENT_FN(OnEntityDestroyedEvent));
		}

		bool OnEntityDestroyedEvent(EntityDestroyedEvent& e)
		{
			ENGINE_CORE_TRACE("Entity Destroyed Event!");
			for (auto const& x : m_Components)
			{
				x.second->EntityDestroyed(e.GetEntityID());
			}
			return false;
		}

		// HELPER

		template<typename T>
		ComponentTypeID GetComponentTypeID()
		{
			return GetFamilyTypeID<IComponent, T>();
		}

		template<typename T>
		Ref<ComponentContainer<T>> GetComponentContainer()
		{
			ComponentTypeID cID = GetComponentTypeID<T>();
			if ((m_Components.find(cID) == m_Components.end()))
				ENGINE_CORE_ASSERT(false, "Component not registered before use");
			return std::static_pointer_cast<ComponentContainer<T>>(m_Components[cID]);
		}

		template<typename T>
		void Register()
		{
			ComponentTypeID cID = GetComponentTypeID<T>();
			m_Components[cID] = CreateRef<ComponentContainer<T>>();
		}

		template<typename T>
		bool IsRegistered()
		{
			ComponentTypeID cID = GetComponentTypeID<T>();
			return (m_Components.find(cID) != m_Components.end());
		}


	};

}