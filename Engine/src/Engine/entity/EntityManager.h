#pragma once

#include "engpch.h"

#include "Engine/Entity/IEntity.h"
#include "Engine/Event/Subject.h"
#include "Engine/Event/EntityEvent.h"
#include "Engine/Utils/Handle.h"

namespace Engine
{

	class EntityManager : public Subject
	{

	public:

		// ACCESSOR
		static EntityManager& Get() { return *s_Instance; }
		SparseSet<EntityID, Ref<IEntity>>& GetEntities() { return m_Entities; }
		
		// ENTITY CREATION / DESTRUCTION
		template<typename T, typename ... Args>
		Ref<T> CreateEntity(Args&& ... args)
		{
			Ref<T> entity = CreateRef<T>(std::forward<Args>(args)...);
			EntityID id = Handle<IEntity>::AcquireHandle();
			entity->SetID(id);
			m_Entities.Insert(id, entity);

			EntityCreatedEvent e(id);
			this->Notify(e);
			return entity;
		}

		void DestroyEntity(EntityID id)
		{
			m_Entities.Erase(id);
			EntityDestroyedEvent e(id);
			this->Notify(e);
		}

		Ref<IEntity> GetEntity(EntityID id) { return m_Entities.Get(id); }

	private:

		static EntityManager* s_Instance;
		SparseSet<EntityID, Ref<IEntity>> m_Entities;
		
	};

}