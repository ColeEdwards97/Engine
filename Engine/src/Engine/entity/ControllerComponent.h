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

		Controller* GetController() { return m_Controller; }
		void SetController(Controller* controller) { m_Controller = controller; }

	private:
		Controller* m_Controller;

	};

}