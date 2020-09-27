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
		virtual void onEvent(Event& e) {}

		inline const std::string& getName() const { return m_debugName; }

		// TODO: bool isEnabled()

	private:
		std::string m_debugName;
	};
}