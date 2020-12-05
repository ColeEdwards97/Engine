#pragma once

#include "Engine/renderer/Shader.h"

namespace Engine
{

	class OpenGLShader : public Shader
	{

	public:

		OpenGLShader(const char* fragShaderPath, const char* vertShaderPath);
		OpenGLShader(std::string fragShaderSrc, std::string vertShaderSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetBool(const std::string& name, bool value);


	private:

		unsigned int m_programID;

	private:

		std::string LoadShader(const char* shaderPath);

	};

}