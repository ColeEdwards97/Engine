#pragma once

#include "Engine/Entity/EntityManager.h"
#include "Engine/Entity/IEntity.h"
#include "Engine/Entity/EntityUtil.h"

namespace Engine
{
	
	template<typename E>
	class Entity : public IEntity
	{
	
		// deletion is handled by EntityManager
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;

	public:

		// CONSTRUCTOR & DESTRUCTOR
		Entity()
		{}

		virtual ~Entity()
		{}

		// ACCESSOR
		virtual const uint32_t GetTypeID() const override { return s_EntityTypeID; };

		
	private:

		static const uint32_t s_EntityTypeID;

	};

	template<typename E>
	const uint32_t Entity<E>::s_EntityTypeID = GetEntityTypeID<E>();

}