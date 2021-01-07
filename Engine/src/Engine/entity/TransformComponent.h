#pragma once

#include "Engine/Entity/Component.h"
#include "Engine/World/Transform.h"

namespace Engine
{

	class TransformComponent : public Component<TransformComponent>
	{

	public:

		TransformComponent() {}
		virtual ~TransformComponent() {}

		Transform& GetTransform() { return m_Transform; }
		
	private:

		Transform m_Transform;

	};

}