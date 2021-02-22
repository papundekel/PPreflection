#pragma once
#include "construct_pack.hpp"
#include "decl_type.hpp"
#include "functional/compose.hpp"
#include "overloaded.hpp"
#include "type_tuple.hpp"

namespace PPreflection
{
	constexpr inline auto get_integral_promotion_type =
		PP::decl_type_copy |
		PP::make_overloaded_pack[PP::functor([]
				(PP::concepts::type auto t)
				{
					return [](PP_GET_TYPE(t)) { return {}; };
				}} + PP::type_tuple<int, unsigned int, long, unsigned long, long long, unsigned long long>] |
		PP::construct_pack;
}
