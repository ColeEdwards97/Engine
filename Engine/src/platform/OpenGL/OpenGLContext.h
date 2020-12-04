#pragma once

#include "Engine/renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Engine
{

	class OpenGLContext : public GraphicsContext
	{

	public:

		OpenGLContext(GLFWwindow* handle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:

		GLFWwindow* m_handle;

	};

}