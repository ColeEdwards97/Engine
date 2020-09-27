#include "engpch.h"

#include "EventHandler.h"

namespace Engine
{
	std::unordered_map<EventType, std::vector<EventListener*>> EventHandler::eventListeners;
}
