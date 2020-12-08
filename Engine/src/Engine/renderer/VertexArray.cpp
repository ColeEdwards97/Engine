#include "engpch.h"

#include "VertexArray.h"
#include "Renderer.h"

#include "platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}