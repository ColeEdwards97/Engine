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

		const SystemTypeID GetTypeID() const override { return GetStaticTypeID(); }
		static SystemTypeID GetStaticTypeID() { return s_SystemTypeID; }

		// Must be implemented in derived class
		virtual void OnEnable() override { static_cast<S*>(this)->OnEnable(); }
		virtual void OnDisable() override { static_cast<S*>(this)->OnDisable(); }
		
		// Must be implemented in derived class
		virtual void OnUpdate(TimeStep ts) override { static_cast<S*>(this)->OnUpdate(ts); }
		virtual void OnEvent(Event& e) override { static_cast<S*>(this)->OnEvent(e); }

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