#include "engpch.h"

#include "OpenGLShader.h"

#include "Engine/Core/Core.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{

	OpenGLShader::OpenGLShader(const char* fragShaderPath, const char* vertShaderPath)
		: OpenGLShader(LoadShader(fragShaderPath), LoadShader(vertShaderPath))
	{
	}
	
	OpenGLShader::OpenGLShader(std::string fragShaderSrc, std::string vertShaderSrc)
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


	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_programID);
	}


	void OpenGLShader::Bind() const
	{
		glUseProgram(m_programID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}



	std::string OpenGLShader::LoadShader(const char* shaderPath)
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


	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
	}


	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
	}


	void OpenGLShader::SetBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
	}


	// TODO: other mats and vecs
	void OpenGLShader::SetVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(m_programID, name.c_str()), 1, glm::value_ptr(value));
	}
	void OpenGLShader::SetVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(m_programID, name.c_str()), 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}


}