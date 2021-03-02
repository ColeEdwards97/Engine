#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <variant>
#include <optional>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <fstream>

#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include <type_traits>
#include <typeindex>
#include <limits>


// Engine Includes
#include "Engine/Core/Core.h"
#include "Engine/Core/Log.h"

// OpenGL Includes
#include "Platform/OpenGL/OpenGLContext.h"

#ifdef ENG_PLATFORM_WINDOWS
#include <Windows.h>
#endif // ENG_PLATFORM_WINDOWS
