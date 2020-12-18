#pragma once

#include "engpch.h"

namespace Engine
{

	using SystemTypeID = std::size_t;

	class ISystem
	{

	public:

		ISystem()
			: m_Enabled(true)
		{}
		virtual ~ISystem() = default;
		virtual const SystemTypeID GetTypeID() const = 0;

		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;

		bool IsEnabled() { return m_Enabled; }
		void SetEnabled(bool enabled);

	private:

		bool m_Enabled;

	};

}