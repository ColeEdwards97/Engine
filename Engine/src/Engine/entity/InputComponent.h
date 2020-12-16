#pragma once

#include "Engine/Entity/Entity.h"
#include "Engine/Entity/Component.h"

namespace Engine
{
	class InputComponent : public Component
	{
	public:
		virtual ~InputComponent() {}

		ALLOWS_MULTIPLE(false);
	};
}
