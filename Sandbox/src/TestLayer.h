#pragma once

#include "Engine.h"

class TestLayer : public Engine::Layer
{
public:

	TestLayer()
		: Layer("Test Layer")
	{}

	void onUpdate() override
	{
		ENGINE_INFO("Layer: {0} onUpdate()", this->getName());
	}

	void onEvent(Engine::Event& e) override
	{
		ENGINE_TRACE("An Event Occurred!");
	}

};