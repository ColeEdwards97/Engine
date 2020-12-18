#pragma once

#include "Engine/Entity/Entity.h"
#include "Engine/Entity/TransformComponent.h"

namespace Engine
{

	template<class T>
	class GameObject : public Entity<T>
	{

	public:

		GameObject()
		{
			AddComponent<TransformComponent>();
		}

		virtual ~GameObject() {}

	};

}