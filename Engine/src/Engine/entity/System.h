#pragma once

#include "Engine/Entity/ISystem.h"

namespace Engine
{

	template<typename S>
	class System : public ISystem
	{

	public:

		// CONSTRUCTOR & DESTRUCTOR
		System()
		{}

		virtual ~System()
		{}

		// ACCESSOR
		virtual const uint32_t GetTypeID() override { return s_SystemTypeID; }

	private:

		static const uint32_t s_SystemTypeID;
		static System<S>* s_SystemInstance;

		static std::unordered_map<uint32_t, std::vector<uint32_t>> m_OwnedComponents;

	};

	template<typename S>
	const uint32_t System<S>::s_SystemTypeID = GetSystemTypeID<S>();

}