#pragma once

#include "Engine/Core/Layer.h"

namespace Engine
{

	class ImGuiLayer : public Layer
	{

	public:

		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_blockEvents = block; }

	private:

		bool m_ImGuiInitialized = false;
		bool m_blockEvents = true;
		float m_time = 0.0f;

	};

}