#include "engpch.h"

#include "Shader.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace Engine
{

	Shader* Shader::Create(const char* fragShaderPath, const char* vertShaderPath)
	{
		// TODO: #ifdefs for other rendering platforms
		return new OpenGLShader(fragShaderPath, vertShaderPath);
	}

	Shader* Shader::Create(std::string fragShaderSrc, std::string vertShaderSrc)
	{
		// TODO: #ifdefs for other rendering platforms
		return new OpenGLShader(fragShaderSrc, vertShaderSrc);
	}

}