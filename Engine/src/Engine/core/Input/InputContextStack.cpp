#include "engpch.h"
#include "InputContextStack.h"

namespace Engine
{

	InputContextStack::InputContextStack()
	{}

	InputContextStack::~InputContextStack()
	{
		for (auto context : m_Contexts)
		{
			delete context;
		}
		m_Contexts.clear();
	}


	void InputContextStack::PushContext(InputContext* context)
	{
		if (std::find(m_Contexts.begin(), m_Contexts.end(), context) == m_Contexts.end())
		{
			m_Contexts.push_back(context);
		}
	}

	void InputContextStack::PopContext(InputContext* context)
	{
		if (auto found = std::find(m_Contexts.begin(), m_Contexts.end(), context); found != m_Contexts.end())
		{
			delete (*found);
			m_Contexts.erase(found);
		}
	}

}