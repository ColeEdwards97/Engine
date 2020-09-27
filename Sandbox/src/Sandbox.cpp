#include <Engine.h>

#include "TestLayer.h"

class Sandbox : public Engine::Application {

public:

	Sandbox() 
	{
		pushLayer(new TestLayer());
	}

	~Sandbox() 
	{

	}
	
};

Engine::Application* Engine::createApplication() 
{
	return new Sandbox();
}
