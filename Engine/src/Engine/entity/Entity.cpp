#include "engpch.h"

#include "Entity.h"

namespace Engine
{

	Entity::~Entity()
	{
		for (Component* c : m_Components)
		{
			delete c;
		}
	}

}