#pragma once
#include "PP/apply_partially.hpp"
#include "PP/concepts/function.hpp"
#include "PP/concepts/fundamental_types.hpp"
#include "PP/concepts/pointable.hpp"
#include "PP/concepts/reference.hpp"
#include "PP/operators.hpp"
#include "PP/tuple_find_dynamic.hpp"

namespace PPreflection
{
	enum class type_class : PP::size_t
	{
		reference,
		Void,
		function,
		unknown_bound_array,
		known_bound_array,
		null,
		integral,
		floating_point,
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

	PP_FUNCTOR(get_type_class_value_t, PP::concepts::type auto t)
	{
		return PP::value<type_class(PP::tuple_find_dynamic(
			PP::cal(PP::partial_tag, PP::value_1, PP_COPY_TYPE(t)),
			PP::make_tuple(PP::is_reference,
						   PP::is_void,
						   PP::is_function,
						   PP::is_unbounded_array,
						   PP::is_bounded_array,
						   PP::is_null,
						   PP::is_integral,
						   PP::is_floating_point,
						   PP::is_pointer,
						   PP::is_pointer_to_member,
						   PP::is_class,
						   PP::is_union,
						   PP::is_enum)))>;
	});
}
