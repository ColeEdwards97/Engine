#pragma once

namespace Engine
{

	class Shader
	{

	public:

		static Shader* Create(const char* fragShaderPath, const char* vertShaderPath);
		static Shader* Create(std::string fragShaderSrc, std::string vertShaderSrc);
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

	};

}