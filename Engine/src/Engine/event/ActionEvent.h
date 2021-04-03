#pragma once
#include "Engine/Event/Event.h"
#include "Engine/Core/Input/Action.h"

namespace Engine
{

	class ActionEvent : public Event
	{
	public:
		Action GetAction() const { return m_Action; }
		
	protected:
		ActionEvent(const Action action)
			: m_Action(action)
		{}

	private:
		Action m_Action;
	};


	class ActionBeginEvent : public ActionEvent
	{
	public:
		ActionBeginEvent(const Action action)
			: ActionEvent(action)
		{}
	};

	class ActionEndEvent : public ActionEvent
	{
	public:
		ActionEndEvent(const Action action)
			: ActionEvent(action)
		{}
	};

}