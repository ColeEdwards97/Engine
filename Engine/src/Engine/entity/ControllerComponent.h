#pragma once

#include "Engine/Entity/Component.h"
#include "Engine/Entity/Controller.h"

namespace Engine
{

	class ControllerComponent : public Component<ControllerComponent>
	{
	public:
		ControllerComponent()
			: m_Controller(nullptr)
		{}
		virtual ~ControllerComponent() {}

		IController* GetController() { return m_Controller; }
		void SetController(IController* controller) { m_Controller = controller; }

	private:
		IController* m_Controller;

	};

}