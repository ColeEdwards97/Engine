#pragma once

#include "engpch.h"
#include "Engine/Core/TimeStep.h"
#include "Engine/Event/Event.h"

namespace Engine
{

	using SystemTypeID = size_t;

	class ISystem
	{

		friend class SystemManager;

	public:
		
		virtual const SystemTypeID GetTypeID() const = 0;

		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		
		virtual void OnUpdate(TimeStep ts) = 0;
		virtual void OnEvent(Event& e) = 0;

		bool IsEnabled() { return m_Enabled; }
		void SetEnabled(bool enabled);

	protected:
		ISystem()
			: m_Enabled(true)
		{}
		virtual ~ISystem() = default;

	private:

		bool m_Enabled;

	};

}