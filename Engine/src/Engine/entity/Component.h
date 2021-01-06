#pragma once

#include "Engine/Entity/IComponent.h"

#include "Engine/Utils/FamilyTypeID.h"

namespace Engine
{

	template<typename C>
	class Component : public IComponent
	{

	public:

		const ComponentTypeID GetTypeID() const override { return s_ComponentTypeID; }

		virtual void OnEnable() override {}
		virtual void OnDisable() override {}
		
	protected:

		Component() = default;
		Component(const Component&) = default;
		Component(Component&&) = default;
		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;

	private:

		static const ComponentTypeID s_ComponentTypeID;

	};

	template<typename C>
	const ComponentTypeID Component<C>::s_ComponentTypeID = GetFamilyTypeID<IComponent, C>();

}