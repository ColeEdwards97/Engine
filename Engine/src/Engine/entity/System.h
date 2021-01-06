#pragma once

#include "Engine/Entity/EntityManager.h"
#include "Engine/Entity/ISystem.h"

#include "Engine/Core/TimeStep.h"
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

		static void OnUpdate(SparseSet<EntityID, Ref<IEntity>> entities, TimeStep ts) { S::OnUpdate(entities, ts); }

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