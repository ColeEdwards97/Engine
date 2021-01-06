#pragma once

#include "Engine/Entity/System.h"

namespace Engine
{

	class ControllerSystem : public System<ControllerSystem>
	{
	public:
		ControllerSystem() {}
		virtual ~ControllerSystem() {}

		void OnEnableImpl();
		void OnDisableImpl();

		void OnUpdateImpl(TimeStep ts);
		void OnEventImpl(Event& e);

	};

}