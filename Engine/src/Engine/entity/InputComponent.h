#pragma once

#include "Entity.h"
#include "Component.h"

namespace Engine
{
	class InputComponent : public Component
	{
	public:
		virtual ~InputComponent() {}
		virtual void onUpdate(Entity& e) = 0;
	};
}
