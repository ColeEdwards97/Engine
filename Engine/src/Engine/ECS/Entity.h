#pragma once

#include "engpch.h"

#include "Engine/Core/null.h"
#include "Engine/Utils/Identifier.h"

namespace Engine
{
	
	class EntityID final
	{
		using id_type = uint64_t;
		using index_type = uint32_t;
		using version_type = uint32_t;
		static constexpr id_type mask = 0xFFFFFFFF;
		static constexpr std::size_t shift = 32UL;

		friend class Registry;

	public:
		EntityID() = default;
		explicit EntityID(index_type index, version_type version) : m_Id((id_type)index | ((id_type)version << shift)) {}
		explicit EntityID(id_type id) : m_Id(id) {}
		EntityID(const EntityID& other) = default;
		EntityID& operator=(const EntityID&) = default;
		EntityID(EntityID&& other) = default;
		EntityID& operator=(EntityID&&) = default;

		[[nodiscard]] const id_type Id() const { return m_Id; }
		[[nodiscard]] const index_type Index() const { return m_Id & mask; }
		[[nodiscard]] const version_type Version() const { return m_Id >> shift; }

		[[nodiscard]] constexpr operator const id_type() const noexcept { return m_Id; }

		[[nodiscard]] bool operator==(const EntityID other) noexcept {
			return (
				this->Id() == other.Id() &&
				this->Index() == other.Index() &&
				this->Version() == other.Version()
				);
		}
		[[nodiscard]] bool operator!=(const EntityID other) noexcept {
			return !(this->operator==(other));
		}

		[[nodiscard]] bool operator==(const null_t& null) noexcept {
			return this->operator==(EntityID{ null });
		}
		[[nodiscard]] bool operator!=(const null_t& null) noexcept {
			return this->operator!=(EntityID{ null });
		}

		[[nodiscard]] bool operator<(const EntityID other) noexcept {
			return this->Id() < other.Id();
		}
		
	private:
		id_type m_Id = null;
		
	};
	
	// null EntityID. not needed. provided anyway for explicity
	template<>
	struct null_traits<EntityID> {
		static constexpr EntityID value = EntityID{};
	};
	
}