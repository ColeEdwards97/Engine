#pragma once

namespace Engine
{
	
	using ComponentTypeID = size_t;

	class IComponent
	{
	public:

		// CONSTRUCTOR & DESTRUCTOR
		IComponent()
			: m_Enabled(true)
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
		bool m_Enabled;

	};

}