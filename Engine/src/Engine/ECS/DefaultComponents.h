#pragma once

#include "Engine/ECS/Component.h"
#include "Engine/World/Transform.h"
#include "Engine/Renderer/Camera.h"

namespace Engine
{


	struct TransformComponent : public Component<TransformComponent>
	{
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Transform& transform)
			: transform(transform)
		{}

		Transform transform = Transform{};

	};

	struct CameraComponent : public Component<CameraComponent>
	{
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const Camera& camera) 
			: camera(camera)
		{}

		Camera camera = Camera{};
	};



	using GameObject = Prototype<TransformComponent>;


}