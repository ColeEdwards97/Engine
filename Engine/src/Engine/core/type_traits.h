#pragma once

namespace Engine
{


	template<typename ... Ts>
	struct type_list {
		using type = type_list;
		static constexpr auto size = sizeof...(Ts);
	};


}