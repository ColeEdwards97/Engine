#include "engpch.h"

#include "IEntity.h"

namespace Engine
{

	void IEntity::SetEnabled(bool enabled)
	{
		
		if (IsEnabled() == enabled)
			return;

		if (enabled)
			OnEnable();

		else
			OnDisable();

		m_Enabled = enabled;

	}

}