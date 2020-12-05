#pragma once

namespace Engine
{

	class Shader
	{

	public:

		Shader(const char* fragShaderPath, const char* vertShaderPath);
		Shader(std::string fragShaderSrc, std::string vertShaderSrc);
		~Shader();
		
		void Bind() const;
		void Unbind() const;

		// utility methods for shader uniforms
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetBool(const std::string& name, bool value);


	private:

		unsigned int m_programID;

	private:

		std::string LoadShader(const char* shaderPath);

	};

}