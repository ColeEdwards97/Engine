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

		virtual void OnEnable() override { static_cast<S*>(this)->OnEnableImpl(); }
		virtual void OnDisable() override { static_cast<S*>(this)->OnDisableImpl(); }

		virtual void OnUpdate(TimeStep ts) override { static_cast<S*>(this)->OnUpdateImpl(ts); }
		virtual void OnEvent(Event& e) override { static_cast<S*>(this)->OnEventImpl(e); }

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