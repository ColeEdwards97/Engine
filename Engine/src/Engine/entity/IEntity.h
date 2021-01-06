#pragma once

#include "Engine/Entity/ComponentManager.h"

namespace Engine
{

	using EntityID = uint64_t;
	using EntityTypeID = size_t;

	class IEntity
	{
	public:

		const EntityID GetID() { return m_EntityID; }
		virtual const EntityTypeID GetTypeID() const = 0;

		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		
		// ACCESSOR
		bool IsEnabled() { return m_Enabled; }
		void SetEnabled(bool enabled);


		// COMPONENT MANAGER HELPERS
		template<typename T>
		Ref<T> AddComponent()
		{
			return m_ComponentManager.AddComponent<T>(m_EntityID);
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

		void SetID(EntityID id) { m_EntityID = id; }

		friend class EntityManager;

	protected:

		EntityID m_EntityID;
		bool m_Enabled;

	private:

		ComponentManager& m_ComponentManager = ComponentManager::Get();

	};

}