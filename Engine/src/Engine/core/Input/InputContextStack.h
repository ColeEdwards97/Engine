#pragma once

#include "Engine/Core/Input/InputContext.h"

namespace Engine
{

	class InputContextStack final
	{
	public:
		InputContextStack();
		~InputContextStack();

		void PushContext(InputContext* context);
		void PopContext(InputContext* context);

		using iterator = std::vector<InputContext*>::iterator;
		using const_iterator = std::vector<InputContext*>::const_iterator;
		using reverse_iterator = std::vector<InputContext*>::reverse_iterator;
		using const_reverse_iterator = std::vector<InputContext*>::const_reverse_iterator;

		iterator begin() { return m_Contexts.begin(); }
		iterator end() { return m_Contexts.end(); }
		const_iterator begin() const { return m_Contexts.begin(); }
		const_iterator end() const { return m_Contexts.end(); }
		reverse_iterator rbegin() { return m_Contexts.rbegin(); }
		reverse_iterator rend() { return m_Contexts.rend(); }
		const_reverse_iterator rbegin() const { return m_Contexts.rbegin(); }
		const_reverse_iterator rend() const { return m_Contexts.rend(); }

	private:
		std::vector<InputContext*> m_Contexts;
	};

}