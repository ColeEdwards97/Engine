#include "engpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

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
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_handle);
	}

}