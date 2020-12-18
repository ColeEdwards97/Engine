#include "engpch.h"

#include "IComponent.h"

namespace Engine
{

	void IComponent::SetEnabled(bool enabled)
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