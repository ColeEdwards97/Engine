#pragma once

namespace Engine
{

	class IEntity
	{

	public:

		// CONSTRUCTOR & DESTRUCTOR
		IEntity();
		virtual ~IEntity();

		// ACCESSOR
		virtual const uint32_t GetTypeID() const = 0;
		const uint32_t GetID() { return m_EntityID; }

		virtual void OnEnable() {}
		virtual void OnDisable() {}

		// STATE
		bool IsActive() const { return m_Active; }
		void SetActive(bool active);

		// OPERATORS
		inline bool operator==(const IEntity& other) const { return m_EntityID == other.m_EntityID; }
		inline bool operator==(const IEntity* other) const { return m_EntityID == other->m_EntityID; }
		inline bool operator!=(const IEntity& other) const { return m_EntityID != other.m_EntityID; }
		inline bool operator!=(const IEntity* other) const { return m_EntityID != other->m_EntityID; }

		// ENTITY MANAGER

		template<typename T>
		T* AddComponent()
		{
			return EntityManager::AddComponent<T>(m_EntityID);
		}

		template<typename T>
		T* GetComponent()
		{
			return EntityManager::GetComponent<T>(m_EntityID);
		}

		template<typename T>
		void RemoveComponent()
		{
			EntityManager::RemoveComponent<T>(m_EntityID);
		}

	protected:

		uint32_t m_EntityID = 0;
		bool m_Active;

	};

}