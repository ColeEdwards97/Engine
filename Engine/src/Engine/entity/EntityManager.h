#pragma once

#include "engpch.h"

#include "Engine/Entity/IEntity.h"

namespace Engine
{

	class EntityManager
	{

	public:

		static EntityManager& Get() { return *s_Instance; }

	private:

		static EntityManager* s_Instance;
		SparseSet<EntityID, Ref<IEntity>> m_Entities;
		
	};

}