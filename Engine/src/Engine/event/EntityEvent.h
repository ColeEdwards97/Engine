#pragma once

#include "Engine/Event/Event.h"
#include "Engine/ECS/Entity.h"

namespace Engine
{

	class EntityEvent : public Event
	{
	public:
		EntityID GetEntityID() const { return m_Id; }

	protected:
		EntityEvent(const EntityID id)
			: m_Id(id)
		{}
	private:
		EntityID m_Id;
	};


	class EntityCreatedEvent : public EntityEvent
	{
	public:
		EntityCreatedEvent(const EntityID id)
			: EntityEvent(id)
		{}
	};


	class EntityDestroyedEvent : public EntityEvent
	{
	public:
		EntityDestroyedEvent(const EntityID id)
			: EntityEvent(id)
		{}
	};

}