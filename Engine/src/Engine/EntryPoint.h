#pragma once

#ifdef ENG_PLATFORM_WINDOWS

extern Engine::Application* Engine::createApplication();

int main(int argc, char** argv) {

	Engine::Log::init();
	ENGINE_CORE_INFO("Core logger initialized");
	ENGINE_INFO("Client logger initialized");

	auto app = Engine::createApplication();
	app->run();
	delete app;
}

#endif // ENG_PLATFORM_WINDOWS
