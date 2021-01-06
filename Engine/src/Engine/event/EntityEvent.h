#pragma once

#include "Engine/Event/Event.h"

namespace Engine
{

	class EntityEvent : public Event
	{

	public:
		EntityEvent(EntityID id)
			: m_EntityID(id)
		{}

		EntityID GetEntityID() const { return m_EntityID; }

	private:
		EntityID m_EntityID;

	};

	class EntityCreatedEvent : public EntityEvent
	{
	public:
		EntityCreatedEvent(EntityID id)
			: EntityEvent(id)
		{}
	};

	class EntityDestroyedEvent : public EntityEvent
	{
	public:
		EntityDestroyedEvent(EntityID id)
			: EntityEvent(id)
		{}
	};

}