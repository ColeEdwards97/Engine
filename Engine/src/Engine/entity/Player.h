#pragma once

#include "LivingEntity.h"

namespace Engine
{
	class Player : public LivingEntity
	{
	public:

		Player(const char* uuid, PlayerInputComponent* playerInputComponent) :
			LivingEntity(playerInputComponent), m_uuid(uuid)
		{}

	private:
		const char* m_uuid;

	};
}