#include "engpch.h"

#include "Controller.h"

#include "Engine/Entity/EntityManager.h"

namespace Engine
{

	Controller::Controller(IController* controller)
		: m_ControllerImpl(controller)
	{}

	Controller::~Controller()
	{
		m_ControllerImpl = nullptr;
	}


	void Controller::OnUpdate(TimeStep ts)
	{
		if (m_ControllerImpl == nullptr)
			return;

		m_ControllerImpl->OnUpdate(ts);
	}

	void Controller::OnEvent(Event& e)
	{
		if (m_ControllerImpl == nullptr)
			return;

		m_ControllerImpl->OnEvent(e);
	}

	void Controller::Possess(EntityID id)
	{
		if (m_ControllerImpl == nullptr)
			return;

		m_ControllerImpl->Possess(id);
	}

	void Controller::Possess(Ref<IEntity> e)
	{
		if (m_ControllerImpl == nullptr)
			return;

		m_ControllerImpl->Possess(e);
	}

	void Controller::Unpossess()
	{
		if (m_ControllerImpl == nullptr)
			return;

		m_ControllerImpl->Unpossess();
	}

}