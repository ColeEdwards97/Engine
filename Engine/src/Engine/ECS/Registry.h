#pragma once

#include "Engine/ECS/Entity.h"
#include "Engine/ECS/Component.h"
#include "Engine/ECS/Storage.h"
#include "Engine/Event/EntityEvent.h"

namespace Engine
{


	class Registry : public Subject
	{

		using storage_type = Scope<sparse_set<EntityID::id_type>>;

		template<typename Component>
		using component_storage_type = Storage<EntityID::id_type, Component>;


	public:


		[[nodiscard]] EntityID Create() {
			
			// obtain id
			const EntityID id = (m_Available == null) ? GenerateIdentifier() : RecycleIdentifier();

			// notify
			EntityCreatedEvent e(id);
			this->Notify(e);

			return id;
		}
		
		// TODO: prototype support

		void Destroy(const EntityID id) {

			// remove components
			RemoveAllComponents(id);

			// release identifier
			ReleaseIdentifier(id);

			// notify
			EntityDestroyedEvent e(id);
			this->Notify(e);
		}
		

		template<typename Component>
		[[nodiscard]] component_storage_type<Component>* Assure() {

			const auto type_id = Component::GetStaticType();

			if (!(type_id < m_Components.size())) {
				m_Components.resize(type_id + 1U);
			}

			if (!m_Components[type_id]) {
				m_Components[type_id].reset(new component_storage_type<Component>());
			}

			return static_cast<component_storage_type<Component>*>(m_Components[type_id].get());
		}

		template<typename Component>
		[[nodiscard]] bool HasComponent(const EntityID id) {
			ENGINE_CORE_ASSERT((Valid(id)), "Entity is invalid");
			const auto type_id = Component::GetStaticType();
			return (type_id < m_Components.size() && m_Components[type_id] && m_Components[type_id].get()->contains(id));
		}

		template<typename ... Components>
		[[nodiscard]] bool HasComponents(const EntityID id) {
			return (HasComponent<Components>(id) && ...);
		}

		template<typename ... Components>
		[[nodiscard]] bool HasComponents(const EntityID id, type_list<Components...>) {
			return (HasComponent<Components>(id) && ...);
		}

		template<typename Component, typename ... Args>
		Component& AddComponent(const EntityID id, Args&& ... args) {
			ENGINE_CORE_ASSERT((is_component_v<Component>), "Type passed to Component parameter is not a valid Component");
			ENGINE_CORE_ASSERT((Valid(id)), "Entity is invalid");
			ENGINE_CORE_ASSERT((!HasComponent<Component>(id)), "Entity already has a component of this type");
			return Assure<Component>()->emplace(id, std::forward<Args>(args)...);
		}

		template<typename ... Components, typename ... Args>
		auto AddComponents(const EntityID id, Args&& ... args) {
			return std::forward_as_tuple(AddComponent<Components>(id, std::forward<Args>(args))...);
		}

		template<typename ... Components>
		auto AddComponents(const EntityID id, type_list<Components...>) {
			return std::forward_as_tuple(AddComponent<Components>(id)...);
		}

		template<typename ... Components, typename ... Args>
		auto AddComponents(const EntityID id, type_list<Components...>, Args&& ... args) {
			return std::forward_as_tuple(AddComponent<Components>(id, std::forward<Args>(args))...);
		}

		template<typename ... Components>
		auto AddComponents(const EntityID id) {
			return std::forward_as_tuple(AddComponent<Components>(id)...);
		}

		template<typename Component>
		void RemoveComponent(const EntityID id) {
			ENGINE_CORE_ASSERT((Valid(id)), "Entity is invalid");
			if (!HasComponent<Component>(id)) return;
			Assure<Component>()->remove(id);
		}

		template<typename ... Components>
		void RemoveComponents(const EntityID id) {
			(RemoveComponent<Components>(id), ...);
		}

		void RemoveAllComponents(const EntityID id) {
			ENGINE_CORE_ASSERT((Valid(id)), "Entity is invalid");
			for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
				(*it)->remove(id);
			}
		}

		[[nodiscard]] bool Valid(const EntityID id) const {
			return (id.Index() < m_Entities.size() && m_Entities[id.Index()] == id);
		}

	private:

		[[nodiscard]] EntityID GenerateIdentifier() {
			return m_Entities.emplace_back(Identifier<EntityID::id_type>::Get<EntityID>());
		}

		[[nodiscard]] EntityID RecycleIdentifier() {
			ENGINE_CORE_ASSERT((m_Available != null), "Available EntityID should not be null here");
			const auto current = m_Available;
			m_Available = m_Entities[current.Index()];
			return m_Entities[current.Index()] = current;
		}
		
		void ReleaseIdentifier(const EntityID id) {
			m_Entities[id.Index()] = m_Available;
			m_Available = EntityID{ id.Index(), id.Version() + 1U };
		}


	private:
		std::vector<EntityID> m_Entities;
		std::vector<storage_type> m_Components;
		EntityID m_Available = null;

	};

}