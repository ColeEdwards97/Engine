#pragma once

#include "Engine/Entity/Component.h"
#include "Engine/World/Transform.h"

namespace Engine
{

	class TransformComponent : public Component
	{

	public:

		TransformComponent() = default;
		TransformComponent(const Transform& transform) :
			m_Transform(transform)
		{}

		Transform& GetTransform() { return m_Transform; }

		ALLOWS_MULTIPLE(false);

	private:

		Transform m_Transform;

	};

}