#include "engpch.h"

#include "Texture.h"
#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Engine
{
	Ref<Texture2D> Texture2D::Create(int width, int height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	ENGINE_CORE_ASSERT(false, "None RendererAPI is not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(width, height);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	ENGINE_CORE_ASSERT(false, "None RendererAPI is not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(path);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}