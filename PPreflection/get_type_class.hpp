#pragma once
#include "template_tuple.hpp"
#include "tuple_find.hpp"
#include "tuple_map.hpp"
#include "functional/curry.hpp"

enum class type_class : std::size_t
{
	reference,
	Void,
	function,
	unknown_bound_array,
	known_bound_array,
	non_void_fundamental,
	pointer,
	pointer_to_member,
	non_union_class,
	Union,
	Enum,

	type,
	pointable,
	referencable,
	object,
	complete_object,
	non_array_object,
	user_defined,
	Class,
};

static constexpr auto get_type_class(auto t) noexcept
{
	return type_class(PP::tuple_find_index(apply, ~PP::apply_template * PP::template_tuple_v<
																			std::is_reference,
																			std::is_void,
																			std::is_function,
																			std::is_unbounded_array,
																			std::is_bounded_array,
																			std::is_fundamental,
																			std::is_pointer,
																			std::is_member_pointer,
																			std::is_class,
																			std::is_union,
																			std::is_enum>));
}
