#pragma once

#include "Engine/Core.h"
#include "event/Event.h"

namespace Engine
{
	class ENGINE_API Layer
	{
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& e) {}

		const std::string& getName() const { return m_debugName; }

		bool enabled = true;

	private:
		std::string m_debugName;
	};
}