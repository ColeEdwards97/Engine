#pragma once

namespace Engine
{

	class GraphicsContext
	{

	public:

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void PrintErrors(const char* func, const char* file, int line) = 0;
		virtual void ClearErrors() = 0;

	};

}