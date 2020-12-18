#pragma once

#include <Engine.h>

class TestEntity : public Engine::Entity<TestEntity>
{

public:

	TestEntity()
	{
		ENGINE_TRACE("Test Entity Created");
		AddComponent<Engine::TransformComponent>();
		SetEnabled(false);
		Engine::Ref<Engine::TransformComponent>& tc = GetComponent<Engine::TransformComponent>();
		SetEnabled(true);
		RemoveComponent<Engine::TransformComponent>();
		Engine::Ref<Engine::TransformComponent>& tc2 = GetComponent<Engine::TransformComponent>();

		if (tc == nullptr)
			ENGINE_WARN("tc is null");
		if (tc2 == nullptr)
			ENGINE_WARN("tc2 is null");
	}

	virtual ~TestEntity()
	{}

	virtual void OnEnable() override
	{
		ENGINE_TRACE("Test Entity Enabled");
	}

	virtual void OnDisable() override
	{
		ENGINE_TRACE("Test Entity Disabled");
	}

};