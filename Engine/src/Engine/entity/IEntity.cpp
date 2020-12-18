#include "engpch.h"

#include "IEntity.h"

namespace Engine
{

	IEntity::IEntity()
		: m_Active(true)
	{}

	IEntity::~IEntity()
	{}

	void IEntity::SetActive(bool active)
	{
		
		if (IsActive() == active)
			return;

		if (active)
			OnEnable();

		else
			OnDisable();

		m_Active = active;

	}

}