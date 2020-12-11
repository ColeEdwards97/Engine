#pragma once

#include "Engine/Entity/Entity.h"
#include "Engine/Entity/InputComponent.h"

namespace Engine
{
	class LivingEntity : public Entity
	{
	public:

		LivingEntity(InputComponent* inputComponent)
			: m_inputComponent(inputComponent)
		{}

	private:
		InputComponent* m_inputComponent;

	};
}