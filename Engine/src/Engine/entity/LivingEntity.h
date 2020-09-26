#pragma once

#include "Entity.h"
#include "InputComponent.h"

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