#pragma once

#include "Engine/Layer.h"

namespace Engine
{

	class ENGINE_API ImGuiLayer : public Layer
	{

	public:

		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& e);

		void blockEvents(bool block) { m_blockEvents = block; }

	private:

		bool m_blockEvents = true;
		float m_time = 0.0f;

	};

}