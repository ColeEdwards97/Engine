#include "engpch.h"

#include "Shader.h"
#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine
{

	Ref<Shader> Shader::Create(const char* fragShaderPath, const char* vertShaderPath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	ENGINE_CORE_ASSERT(false, "None RendererAPI is not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(fragShaderPath, vertShaderPath);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(std::string fragShaderSrc, std::string vertShaderSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	ENGINE_CORE_ASSERT(false, "None RendererAPI is not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(fragShaderSrc, vertShaderSrc);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}