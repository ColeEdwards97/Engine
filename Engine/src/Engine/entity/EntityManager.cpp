#include "engpch.h"

#include "EntityManager.h"

namespace Engine
{

	EntityManager* EntityManager::s_Instance = new EntityManager();

	SparseSet<uint32_t, IEntity*> EntityManager::m_Entities = SparseSet<uint32_t, IEntity*>();

	SparseSet<uint32_t, IComponent*> EntityManager::m_Components = SparseSet<uint32_t, IComponent*>();
	
	SparseSet<uint32_t, ISystem*> EntityManager::m_Systems = SparseSet<uint32_t, ISystem*>();
	std::unordered_map<uint32_t, ISystem*> m_ComponentSystemMap = std::unordered_map<uint32_t, ISystem*>();

}