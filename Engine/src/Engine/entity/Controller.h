#pragma once

#include "Engine/Core/TimeStep.h"
#include "Engine/Event/Event.h"
#include "Engine/Entity/IEntity.h"

namespace Engine
{
	// TODO: make templated and keep a pawn reference
	class Controller
	{
	public:

		Controller() {}
		virtual ~Controller() {}
		
		virtual void OnUpdate(TimeStep ts) = 0;
		virtual void OnEvent(Event& e) = 0;

		virtual void Possess(EntityID id) = 0;
		virtual void Possess(Ref<IEntity> e) = 0;
		virtual void Unpossess() = 0;

	};

}