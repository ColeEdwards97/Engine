#include "engpch.h"

#include "ISystem.h"

namespace Engine
{

	void ISystem::SetEnabled(bool enabled)
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