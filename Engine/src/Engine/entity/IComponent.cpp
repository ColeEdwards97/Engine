#include "engpch.h"

#include "IComponent.h"

namespace Engine
{

	IComponent::IComponent()
		: m_Active(true)
	{}

	IComponent::~IComponent()
	{}

	void IComponent::SetActive(bool active)
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