#pragma once

#include "Engine/SparseSet.h"
#include "Engine/Entity/ISystem.h"
#include "Engine/Utils/FamilyTypeID.h"

namespace Engine
{

	class SystemManager
	{
	public:

		// ACCESSOR
		static SystemManager& Get() { return *s_Instance; }
		SparseSet<SystemTypeID, Ref<ISystem>>& GetSystems() { return m_Systems; }

		// SYSTEM REGISTRATION
		template<typename T>
		void CreateSystem()
		{
			Ref<T> system = CreateRef<T>();
			m_Systems.Insert(GetSystemTypeID<T>(), system);
		}

		Ref<ISystem> GetSystem(SystemTypeID id) { return m_Systems.Get(id); }
		
		template<typename T>
		Ref<T> GetSystem() { return std::static_pointer_cast<T>(m_Systems.Get(GetSystemTypeID<T>())); }

	private:

		static SystemManager* s_Instance;
		SparseSet<SystemTypeID, Ref<ISystem>> m_Systems;

	private:

		// HELPER
		template<typename T>
		SystemTypeID GetSystemTypeID()
		{
			return GetFamilyTypeID<ISystem, T>();
		}

	};

}