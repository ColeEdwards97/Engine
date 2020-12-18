#pragma once

#include "Engine/Entity/IComponent.h"
#include "Engine/Entity/EntityUtil.h"

namespace Engine
{

	template<typename C>
	class Component : public IComponent
	{

	public:

		// CONSTRUCTOR & DESTRUCTOR
		Component()
		{}

		virtual ~Component()
		{}

		// ACCESSOR
		virtual const uint32_t GetTypeID() const override { return s_ComponentTypeID; };

	private:

		static const uint32_t s_ComponentTypeID;

	};

	template<typename C>
	const uint32_t Component<C>::s_ComponentTypeID = GetComponentTypeID<C>();

}