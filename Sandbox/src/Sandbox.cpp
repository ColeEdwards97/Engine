#include <Engine.h>

#include "TestLayer.h"

class Sandbox : public Engine::Application {

public:

	Sandbox() 
	{
		PushLayer(new TestLayer());
	}

	~Sandbox() 
	{

	}
	
};

Engine::Application* Engine::CreateApplication() 
{
	return new Sandbox();
}
