#pragma once

#include "Player.h"
#include "InputComponent.h"

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