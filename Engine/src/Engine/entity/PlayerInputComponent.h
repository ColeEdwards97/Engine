#pragma once

#include "Player.h"
#include "InputComponent.h"

namespace Engine
{
	class PlayerInputComponent : public InputComponent
	{
	public:

		void onUpdate(Player& p)
		{
			// do stuff
		}

	};
}