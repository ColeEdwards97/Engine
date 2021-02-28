#pragma once

#include "Engine/sparse_set.h"

namespace Engine
{

	template<typename Entity, typename Component>
	class Storage : public sparse_set<Entity>
	{

		using value_type = Component;
		using underlying_type = sparse_set<Entity>;
		using size_type = typename underlying_type::size_type;

	public:
		
		template<typename ... Args>
		value_type& emplace(const Entity e, Args&& ... args) {

			if constexpr (std::is_aggregate_v<value_type>) {
				m_Components.push_back(value_type{ std::forward<Args>(args)... });
			}
			else {
				m_Components.emplace_back(std::forward<Args>(args)...);
			}

			underlying_type::emplace(e);
			return m_Components.back();
		}

	private:

		virtual void swap_and_pop(const size_type pos) override final {
			auto other = std::move(m_Components.back());
			m_Components[pos] = std::move(other);
			m_Components.pop_back();
		}

	private:
		std::vector<Component> m_Components;	//TODO: memory pool

	};

}