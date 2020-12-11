#pragma once

#include "Engine/Renderer/Shader.h"

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

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetBool(const std::string& name, bool value) override;
		// TODO: set vecs and mats
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;


	private:
		
		unsigned int m_programID;

	private:

		std::string LoadShader(const char* shaderPath);

	};

}