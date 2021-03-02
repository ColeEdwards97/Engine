#include "engpch.h"

#include "Engine/Core/Platform.h"
#include <GLFW/glfw3.h>

namespace Engine
{

	const float Platform::GetTime() {
		return (float)glfwGetTime();
	}

}