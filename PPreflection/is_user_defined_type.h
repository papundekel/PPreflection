#pragma once
#include <type_traits>
#include "map_v.hpp"
#include "disjunction.hpp"
#include "template_tuple.hpp"
#include "tuple_map.hpp"
#include "map_v.hpp"

constexpr inline auto is_user_defined_type = PP::disjunction(PP::tuple_map(PP::map_v, PP::template_tuple<std::is_class, std::is_union, std::is_enum>));
