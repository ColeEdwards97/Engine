#pragma once

#include "Engine/Entity/ComponentManager.h"

namespace Engine
{

	using EntityID = uint64_t;
	using EntityTypeID = size_t;

	class IEntity
	{

		friend class EntityManager;

	public:

		const EntityID GetID() { return m_EntityID; }
		virtual const EntityTypeID GetTypeID() const = 0;

		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		
		// ACCESSOR
		bool IsEnabled() { return m_Enabled; }
		void SetEnabled(bool enabled);


		// COMPONENT MANAGER HELPERS
		template<typename T, typename ... Args>
		void AddComponent(Args&& ... args)
		{
			m_ComponentManager.AddComponent<T>(m_EntityID, std::forward<Args>(args)...);
		}
		
		template<typename T>
		Ref<T> GetComponent()
		{
			return m_ComponentManager.GetComponent<T>(m_EntityID);
		}
		
		template<typename T>
		void RemoveComponent()
		{
			m_ComponentManager.RemoveComponent<T>(m_EntityID);
		}

	protected:

		// CONSTRUCTOR & DESTRUCTOR
		IEntity()
			: m_EntityID(0), m_Enabled(true)
		{}
		virtual ~IEntity() = default;

		// Entity ID is set by the EntityManager when creating the Entity
		void SetID(EntityID id) { m_EntityID = id; }

	protected:

		EntityID m_EntityID;
		bool m_Enabled;

	private:

		ComponentManager& m_ComponentManager = ComponentManager::Get();

	};

}