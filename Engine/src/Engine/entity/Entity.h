#pragma once

#include "Engine/Entity/IEntity.h"

#include "Engine/Utils/FamilyTypeID.h"

namespace Engine
{
	
	template<typename E>
	class Entity : public IEntity
	{

	public:

		const EntityID GetID() const { return m_EntityID; }
		const EntityTypeID GetTypeID() const override { return GetStaticTypeID(); }
		static EntityTypeID GetStaticTypeID() { return s_EntityTypeID; }
		
		virtual void OnEnable() override {}
		virtual void OnDisable() override {}
		
	protected:

		Entity() = default;
		Entity(const Entity&) = default;
		Entity(Entity&&) = default;
		Entity& operator=(const Entity&) = delete;
		Entity& operator=(Entity&&) = delete;

	private:

		static const EntityTypeID s_EntityTypeID;

	};

	template<typename E>
	const EntityTypeID Entity<E>::s_EntityTypeID = GetFamilyTypeID<IEntity, E>();

}