#pragma once

#include "Engine.h"

#include "imgui/imgui.h"

class TestLayer : public Engine::Layer
{
public:

	TestLayer()
		: Layer("Test Layer")
	{}

	void OnUpdate() override
	{
		//ENGINE_INFO("Layer: {0} onUpdate()", this->getName());
	}

	void OnEvent(Engine::Event& e) override
	{
		//ENGINE_TRACE("An Event Occurred!");
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world!");
		ImGui::End();
	}

};