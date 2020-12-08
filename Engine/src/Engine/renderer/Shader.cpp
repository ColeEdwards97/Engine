#include "engpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace Engine
{

	Shader* Shader::Create(const char* fragShaderPath, const char* vertShaderPath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLShader(fragShaderPath, vertShaderPath);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Shader* Shader::Create(std::string fragShaderSrc, std::string vertShaderSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLShader(fragShaderSrc, vertShaderSrc);
		}

		ENGINE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}