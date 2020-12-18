#pragma once

#include "Engine/Entity/IEntity.h"
#include "Engine/Entity/IComponent.h"
#include "Engine/Entity/ISystem.h"

namespace Engine
{

	template<typename F>
	class FamilyID
	{
	public:

		template<typename E>
		static uint32_t Type() noexcept
		{
			static const uint32_t s_Value = Identifier();
			return s_Value;
		}

	private:

		static uint32_t Identifier() noexcept
		{
			static uint32_t s_Value = 0;
			return s_Value++;
		}
	};

	template<typename E>
	static const uint32_t GetEntityTypeID() { return FamilyID<IEntity>().Type<E>(); }

	template<typename C>
	static const uint32_t GetComponentTypeID() { return FamilyID<IComponent>().Type<C>(); }

	template<typename S>
	static const uint32_t GetSystemTypeID() { return FamilyID<ISystem>().Type<S>(); }

}