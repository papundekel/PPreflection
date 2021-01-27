#pragma once
#include <type_traits>
#include "functional/disjunction.hpp"
#include "functional/curry.hpp"
#include "template_tuple.hpp"
#include "tuple_map.hpp"

constexpr inline auto is_user_defined_type =
	PP::disjunction(~PP::apply_template + PP::template_tuple_v<std::is_class, std::is_union, std::is_enum>);
