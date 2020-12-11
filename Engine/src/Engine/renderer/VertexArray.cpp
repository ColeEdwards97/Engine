#include "engpch.h"

#include "VertexArray.h"
#include "Engine/Renderer/Renderer.h"

#include "platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}