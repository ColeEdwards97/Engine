#pragma once

#include "Engine/Core/TimeStep.h"
#include "Engine/Event/Event.h"

namespace Engine
{
	class Layer
	{
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		const std::string& GetName() const { return m_debugName; }

		bool enabled = true;

	private:
		std::string m_debugName;
	};
}