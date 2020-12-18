#pragma once

#include "Engine/SparseSet.h"

#include "Engine/Entity/EntityUtil.h"
#include "Engine/Entity/IEntity.h"
#include "Engine/Entity/IComponent.h"
#include "Engine/Entity/ISystem.h"

/* TEMP */
#include "Engine/Math/Random.h"
/* TEMP */

namespace Engine
{

	class EntityManager
	{

	public:

		/* ENTITIES */
		template<typename T>
		static uint32_t CreateEntity()
		{
			uint32_t id = Random<uint32_t>(0, 64);
			m_Entities.Insert(id, new T());
			return id;
		}

		static IEntity* GetEntity(const uint32_t id)
		{
			return nullptr;
		}

		/* COMPONENTS */

		template<typename T>
		static T* AddComponent(const uint32_t id)
		{
			// TESTING ONLY
			uint32_t c_id = id + GetComponentTypeID<T>();
			m_Components.Insert(c_id, new T());
			//m_Components.Insert(id, new T());
			return GetComponent<T>(id);
		}

		template<typename T>
		static T* GetComponent(const uint32_t id)
		{
			uint32_t c_id = id + GetComponentTypeID<T>();
			return reinterpret_cast<T*>(m_Components.Get(c_id));
		}

		template<typename T>
		static void RemoveComponent(const uint32_t id)
		{
			m_Components.Erase(id);
		}


	private:

		static SparseSet<uint32_t, IEntity*> m_Entities;

		// map<ComponentTypeID, SparseSet<EntityID, Component>>
		static SparseSet<uint32_t, IComponent*> m_Components;
		
		static SparseSet<uint32_t, ISystem*> m_Systems;
		static std::unordered_map<uint32_t, ISystem*> m_ComponentSystemMap;

		static EntityManager* s_Instance;

	};

}