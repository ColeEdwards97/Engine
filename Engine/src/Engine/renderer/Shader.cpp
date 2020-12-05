#include "engpch.h"

#include "Shader.h"

#include "glad/glad.h"

namespace Engine
{

	Shader::Shader(const char* fragShaderPath, const char* vertShaderPath)
		: Shader(LoadShader(fragShaderPath), LoadShader(vertShaderPath))
	{}
	
	Shader::Shader(std::string fragShaderSrc, std::string vertShaderSrc)
	{
		const GLchar* fragShaderCode = (const GLchar*)fragShaderSrc.c_str();
		const GLchar* vertShaderCode = (const GLchar*)vertShaderSrc.c_str();

		/* COMPILE SHADERS */

		GLuint fragID;
		GLuint vertID;

		GLint success;

		// vertex shader
		vertID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertID, 1, &vertShaderCode, nullptr);
		glCompileShader(vertID);
		glGetShaderiv(vertID, GL_VERTEX_SHADER, &success);
		if (success == GL_FALSE)
		{

			GLint maxLength = 0;
			glGetShaderiv(vertID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertID);

			// log the error
			ENGINE_CORE_ERROR("INFOLOG: {0}", infoLog.data());
			ENGINE_CORE_ASSERT(false, "FAILED TO COMPILE VERTEX SHADER.")
		}

		// fragment shader
		fragID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragID, 1, &fragShaderCode, nullptr);
		glCompileShader(fragID);
		glGetShaderiv(fragID, GL_FRAGMENT_SHADER, &success);
		if (success == GL_FALSE)
		{

			GLint maxLength = 0;
			glGetShaderiv(fragID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore. Either of them. Don't leak shaders.
			glDeleteShader(vertID);
			glDeleteShader(fragID);

			// log the error
			ENGINE_CORE_ERROR("INFOLOG: {0}", infoLog.data());
			ENGINE_CORE_ASSERT(false, "FAILED TO COMPILE FRAGMENT SHADER.")

		}

		// shader program
		m_programID = glCreateProgram();
		glAttachShader(m_programID, vertID);
		glAttachShader(m_programID, fragID);
		glLinkProgram(m_programID);
		glGetProgramiv(m_programID, GL_PROGRAM, &success);
		if (success == GL_FALSE)
		{

			GLint maxLength = 0;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_programID);

			// Don't leak shaders either.
			glDeleteShader(vertID);
			glDeleteShader(fragID);

			// log the  error
			ENGINE_CORE_ERROR("INFOLOG: {0}", infoLog.data());
			ENGINE_CORE_ASSERT(false, "FAILED TO LINK SHADER PROGRAM.")

		}

		// detach shaders
		glDetachShader(m_programID, fragID);
		glDetachShader(m_programID, vertID);

	}


	Shader::~Shader()
	{
		glDeleteProgram(m_programID);
	}

	
	std::string Shader::LoadShader(const char* shaderPath)
	{
		std::string shaderSrc;
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		/* LOAD THE SHADERS */
		try
		{
			// open shader files
			shaderFile.open(shaderPath);

			// create string stream
			std::stringstream fragShaderStream;
			
			// read from file's buffers into streams
			fragShaderStream << shaderFile.rdbuf();
			
			// close file handles
			shaderFile.close();
			
			// convert stream to string
			shaderSrc = fragShaderStream.str();
			
		}
		catch (std::ifstream::failure e)
		{
			ENGINE_CORE_ERROR("{0}", e.what());
			ENGINE_CORE_ASSERT(false, "FAILED TO LOAD SHADER");
		}

		return shaderSrc;

	}


	void Shader::Bind() const
	{
		glUseProgram(m_programID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
	}


	void Shader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
	}


	void Shader::SetBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
	}

}