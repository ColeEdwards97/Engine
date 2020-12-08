#pragma once

namespace Engine
{

	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};


	class Renderer
	{

	public:

		static RendererAPI GetAPI() { return s_RendererAPI; }
		static void SetAPI(RendererAPI rendererAPI) { s_RendererAPI = rendererAPI; }

	private:

		static RendererAPI s_RendererAPI;

	};

}