#pragma once
#include <type_traits>
#include "Engine/Core/Core.h"
#include "Engine/Core/type_traits.h"
#include "Engine/Utils/Identifier.h"

namespace Engine
{
	
	template<typename C = void>
	class Component
	{
		friend class Registry;
		using type_id_type = std::uint64_t;

	public:
		static type_id_type GetStaticType() { return s_TypeId; }
		const type_id_type GetType() const { return GetStaticType(); }

	protected:
		Component() = default;
		Component(const Component&) = default;
		Component(Component&&) = default;
		Component& operator=(const Component&) = default;
		Component& operator=(Component&&) = default;
		virtual ~Component() = default;

	private:
		static const type_id_type s_TypeId;
	};
	template<typename C>
	const typename Component<C>::type_id_type Component<C>::s_TypeId = GetFamilyTypeIdentifier<Component<>, C, type_id_type>();

	
	template<typename C>
	struct is_component {
		static constexpr bool value = std::is_base_of_v<Component<C>, C>;
	};

	template<typename C>
	inline constexpr bool is_component_v = is_component<C>::value;

	template<typename ... Components>
	struct Prototype {
		static_assert((is_component_v<Components> && ...), "All Components must inherit from Component<C>");
		using type = type_list<Components...>;
	};

}