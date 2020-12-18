#pragma once

namespace Engine
{

	class IComponent
	{

	public:

		// CONSTRUCTOR & DESTRUCTOR
		IComponent();
		virtual ~IComponent();

		// VIRTUAL
		virtual void OnEnable() {};
		virtual void OnDisable() {};

		// ACCESSOR
		virtual const uint32_t GetTypeID() const = 0;

		// STATE
		bool IsActive() const { return m_Active; }
		void SetActive(bool active);

	private:

		bool m_Active;

	};

}