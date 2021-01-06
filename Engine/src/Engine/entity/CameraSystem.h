#pragma once

#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"

#include "Engine/Entity/System.h"
#include "Engine/Entity/Camera.h"

namespace Engine
{

	class CameraSystem : System<CameraSystem>
	{
	public:
		CameraSystem() {}
		virtual ~CameraSystem() {}

		static void OnUpdate(SparseSet<EntityID, Ref<IEntity>> entities, TimeStep ts)
		{
			for (auto const & x : entities)
			{
				Ref<CameraComponent> camera = (*x).GetComponent<CameraComponent>();
				Ref<TransformComponent> transform = (*x).GetComponent<TransformComponent>();
				Ref<CameraControllerComponent> controller = (*x).GetComponent<CameraControllerComponent>();

				if (camera != nullptr && transform != nullptr && controller != nullptr)
				{
					if (Input::IsKeyPressed(INPUT_KEY_W))
					{
						transform->GetTransform().Translate(controller->GetPanSpeed() * ts, transform->GetTransform().GetFront());
					}
				}

			}
		}

	};

}