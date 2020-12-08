#include "engpch.h"

#include "RenderCommand.h"

#include "platform/OpenGL/OpenGLRendererAPI.h"

namespace Engine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}