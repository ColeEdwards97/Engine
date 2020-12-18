#pragma once

#include "Engine/Entity/ISystem.h"

#include "Engine/Utils/FamilyTypeID.h"

namespace Engine
{

	template<typename S>
	class System : public ISystem
	{
	
	public:

		const SystemTypeID GetTypeID() const override { return s_SystemTypeID; }

		virtual void OnEnable() override {}
		virtual void OnDisable() override {}

	protected:

		System() = default;
		System(const System&) = default;
		System(System&&) = default;
		System& operator=(const System&) = delete;
		System& operator=(System&&) = delete;

	private:

		static const SystemTypeID s_SystemTypeID;
		
	};

	template<typename S>
	const SystemTypeID System<S>::s_SystemTypeID = GetFamilyTypeID<ISystem, S>();

}