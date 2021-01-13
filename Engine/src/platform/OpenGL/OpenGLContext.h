#pragma once

#include "Engine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Engine
{

	class OpenGLContext : public GraphicsContext
	{

	public:

		OpenGLContext(GLFWwindow* handle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
		
		virtual void PrintErrors(const char* func, const char* file, int line) { StaticPrintErrors(func, file, line); }
		static void StaticPrintErrors(const char* func, const char* file, int line);
		virtual void ClearErrors() { StaticClearErrors(); }
		static void StaticClearErrors();

	private:

		GLFWwindow* m_handle;

	};

}

#ifdef ENG_DEBUG
#define GL_CALL(x) ::Engine::OpenGLContext::StaticClearErrors(); x; ::Engine::OpenGLContext::StaticPrintErrors(#x, __FILE__, __LINE__);
#else
#define GL_CALL(x) x;
#endif // ENG_DEBUG
