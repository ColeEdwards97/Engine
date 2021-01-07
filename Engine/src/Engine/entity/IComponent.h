#pragma once

namespace Engine
{
	
	using ComponentTypeID = size_t;

	class IComponent
	{

		friend class ComponentManager;

	public:

		virtual const ComponentTypeID GetTypeID() const = 0;

		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;

		// ACCESSOR
		bool IsEnabled() { return m_Enabled; }
		void SetEnabled(bool enabled);

		// ENTITY MANAGER HELPERS
		// TODO: should entity ids be stored?

	protected:
		// CONSTRUCTOR & DESTRUCTOR
		IComponent()
			: m_Enabled(true)
		{}
		virtual ~IComponent() = default;

	protected:
		bool m_Enabled;

	};

}