#pragma once

#include "Engine/Entity/Component.h"

namespace Engine
{
	class Entity
	{

	public:

		Entity() {};
		Entity(const Entity&) = default;
		virtual ~Entity();
		//~Entity();

		//virtual void OnUpdate() = 0;

		template<typename T>
		T& GetComponent()
		{
			ENGINE_CORE_ASSERT(HasComponent<T>(), "Entity does not have a Component of provided type");
			// TODO: return components that have multiples
			auto found = std::find_if(
				m_Components.begin(),
				m_Components.end(),
				[](Component* const c) { return typeid(T) == typeid(*c); }
			);
			return static_cast<T&>(**found);
		}
		
		template<typename T>
		T& AddComponent(T* component)
		{
			if (HasComponent<T>() && !AllowsMultiple<T>())
				ENGINE_CORE_ASSERT(false, "Entity already has Component of provided type");
			m_Components.push_back(component);
			return static_cast<T&>(*(m_Components.back()));
		}

		template<typename T>
		void RemoveComponent()
		{
			ENGINE_CORE_ASSERT(HasComponent<T>(), "Entity does not have a Component of provided type");
			m_Components.erase(
				std::remove_if(
					m_Components.begin(), 
					m_Components.end(), 
					[](Component* const c) { return typeid(T) == typeid(*c); }
				),
				m_Components.end()
			);
		}

		template<typename T>
		bool HasComponent()
		{
			return std::any_of(
				m_Components.begin(),
				m_Components.end(),
				[](Component* const c) { return typeid(T) == typeid(*c); }
			);
		}

	private:

		template<typename T>
		bool AllowsMultiple()
		{
			return T::AllowsMultipleStatic();
		}

	private:
		
		// TODO: initialize id
		int m_ID = 0;
		std::vector<Component*> m_Components;
		

	};


}