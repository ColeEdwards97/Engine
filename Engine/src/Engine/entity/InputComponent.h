#pragma once

#include "Engine/Entity/Entity.h"
#include "Engine/Entity/Component.h"

namespace Engine
{
	class InputComponent : public Component
	{
	public:
		virtual ~InputComponent() {}
		virtual void OnUpdate(Entity& e) = 0;
	};
}
