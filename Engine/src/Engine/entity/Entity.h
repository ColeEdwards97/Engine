#pragma once


namespace Engine
{
	class Entity
	{
	public:
		Entity() {}
		virtual ~Entity() {}
		virtual void onUpdate() = 0;

		void addComponent(Component* component);
		void removeComponent(Component* component);

	};


}