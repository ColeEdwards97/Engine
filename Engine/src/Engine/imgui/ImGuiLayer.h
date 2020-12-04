#pragma once

#include "Engine/Layer.h"

namespace Engine
{

	class ImGuiLayer : public Layer
	{

	public:

		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onEvent(Event& e) override;
		virtual void onImGuiRender() override;

		void begin();
		void end();

		void blockEvents(bool block) { m_blockEvents = block; }

	private:

		bool m_ImGuiInitialized = false;
		bool m_blockEvents = true;
		float m_time = 0.0f;

	};

}