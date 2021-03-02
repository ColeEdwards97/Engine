#include "engpch.h"

#include "GraphicsContext.h"
#include "Engine/Renderer/Renderer.h"

namespace Engine
{

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	ENGINE_CORE_ASSERT(false, "None RendererAPI is not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}