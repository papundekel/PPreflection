#pragma once
#include "type_t.h"
#include <type_traits>
#include "get_type.h"

#include "types/non_union_class_type.h"
#include "types/union_type.h"
#include "types/enum_type.h"
#include "types/pointer_type.h"
#include "types/pointer_to_member_type.h"
#include "types/non_void_fundamental_type.h"
#include "types/known_bound_array_type.h"
#include "types/unknown_bound_array_type.h"
#include "types/function_type.h"
#include "types/void_type.h"
#include "types/reference_type.h"

namespace detail
{
	template <typename T>
	constexpr auto get_type_class_helper() noexcept
	{
		struct error{};

		if constexpr (std::is_reference_v<T>)
			return type_t<reference_type>{};
		else if constexpr (std::is_void_v<T>)
			return type_t<void_type>{};
		else if constexpr (std::is_function_v<T>)
			return type_t<function_type>{};
		else if constexpr (std::is_unbounded_array_v<T>)
			return type_t<unknown_bound_array_type>{};
		else if constexpr (std::is_bounded_array_v<T>)
			return type_t<known_bound_array_type>{};
		else if constexpr (std::is_fundamental_v<T>)
			return type_t<non_void_fundamental_type>{};
		else if constexpr (std::is_pointer_v<T>)
			return type_t<pointer_type>{};
		else if constexpr (std::is_member_pointer_v<T>)
			return type_t<pointer_to_member_type>{};
		else if constexpr (std::is_class_v<T>)
			return type_t<class_type>{};
		else if constexpr (std::is_union_v<T>)
			return type_t<union_type>{};
		else if constexpr (std::is_enum_v<T>)
			return type_t<enum_type>{};
		else
			return error{};
	}
}

template <typename T>
using get_type_class = get_type<decltype(detail::get_type_class_helper<T>())>;
