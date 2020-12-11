#pragma once

#include "Engine/Entity/Player.h"
#include "Engine/Entity/InputComponent.h"

namespace Engine
{
	class PlayerInputComponent : public InputComponent
	{
	public:

		void OnUpdate(Player& p)
		{
			// do stuff
		}

	};
}