#pragma once

#include "engpch.h"

namespace Engine
{

	class ISystem
	{

	public:

		// CONSTRUCTOR & DESTRUCTOR
		ISystem();
		virtual ~ISystem();

		// ACCESSOR
		virtual const uint32_t GetTypeID() const = 0;

	private:

		const uint32_t m_SystemID;

	};

}