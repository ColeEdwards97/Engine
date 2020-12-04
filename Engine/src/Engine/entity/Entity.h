#pragma once


namespace Engine
{
	class Entity
	{
	public:
		Entity() {}
		virtual ~Entity() {}
		virtual void OnUpdate() = 0;

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);

	};


}