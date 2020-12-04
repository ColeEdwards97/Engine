#pragma once

#ifdef ENG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv) {

	Engine::Log::Init();
	ENGINE_CORE_INFO("Core logger initialized");
	ENGINE_INFO("Client logger initialized");

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif // ENG_PLATFORM_WINDOWS
