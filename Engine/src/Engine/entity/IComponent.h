#pragma once

namespace Engine
{

	using ComponentTypeID = std::size_t;

	class IComponent
	{
	public:

		// CONSTRUCTOR & DESTRUCTOR
		IComponent()
			: m_Owner(0), m_Enabled(true)
		{}
		virtual ~IComponent() = default;
		virtual const ComponentTypeID GetTypeID() const = 0;

		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;

		// ACCESSOR
		bool IsEnabled() { return m_Enabled; }
		void SetEnabled(bool enabled);

		// ENTITY MANAGER HELPERS


	protected:

		EntityID m_Owner;
		bool m_Enabled;

	};

}