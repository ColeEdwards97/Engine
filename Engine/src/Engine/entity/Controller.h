#pragma once

#include "Engine/Entity/IController.h"

namespace Engine
{

	class Controller
	{
	public:

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

		void Possess(EntityID id);
		void Possess(Ref<IEntity> e);
		void Unpossess();

	protected:

		Controller(IController* controller);
		~Controller();

	private:
		IController* m_ControllerImpl;
		
	};

}