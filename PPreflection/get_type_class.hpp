#pragma once
#include "concepts/function.hpp"
#include "concepts/pointable.hpp"
#include "concepts/reference.hpp"
#include "functional/operators.hpp"
#include "template_tuple.hpp"
#include "tuple_find_index.hpp"

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

static constexpr auto get_type_class(PP::concepts::type auto t) noexcept
{
	return type_class(PP::tuple_find_index(PP::cal(PP::partial_tag, PP::value_1, t)
		PP::make_tuple(
			PP::is_reference,
			PP::is_void,
			PP::is_function,
			PP::is_unbounded_array,
			PP::is_bounded_array,
			PP::is_fundamental,
			PP::is_pointer,
			PP::is_member_pointer,
			PP::is_class,
			PP::is_union,
			PP::is_enum)));
}
