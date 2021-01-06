#include "engpch.h"

#include "ECS.h"

namespace Engine
{
	ECS* ECS::s_Instance = new ECS();

	void ECS::Init()
	{
		GetEntityManager().RegisterObserver(&GetComponentManager());
	}



}