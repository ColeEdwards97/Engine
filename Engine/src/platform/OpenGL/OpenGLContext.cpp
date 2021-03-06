#include "engpch.h"
#include "OpenGLContext.h"

#include "Engine/Core/Core.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine
{

	OpenGLContext::OpenGLContext(GLFWwindow* handle)
		: m_handle(handle)
	{
		ENGINE_CORE_ASSERT(handle, "Window Handle is null")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_handle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_CORE_ASSERT(status, "Failed to initialize glad");

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glDisable(GL_BLEND);

		// get what graphics vendor, card, and driver we're using
		ENGINE_CORE_INFO("Renderer intitialized graphics context. Using:");
		ENGINE_CORE_INFO("  VENDOR:\t{0}", glGetString(GL_VENDOR));
		ENGINE_CORE_INFO("  RENDERER:\t{0}", glGetString(GL_RENDERER));
		ENGINE_CORE_INFO("  VERSION:\t{0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_handle);
	}

	void OpenGLContext::StaticPrintErrors(const char* func, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			ENGINE_CORE_ERROR("OpenGLError [{0}]: {1} in file {2} line {3}", error, func, file, line);
		}
	}

	void OpenGLContext::StaticClearErrors()
	{
		while (glGetError() != GL_NO_ERROR);
	}

}