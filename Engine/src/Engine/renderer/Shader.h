#pragma once

namespace Engine
{

	class Shader
	{

	public:

		virtual ~Shader() = default;

		static Shader* Create(const char* fragShaderPath, const char* vertShaderPath);
		static Shader* Create(std::string fragShaderSrc, std::string vertShaderSrc);
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetBool(const std::string& name, bool value) = 0;

	};

}