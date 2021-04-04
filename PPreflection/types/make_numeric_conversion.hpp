#pragma once
#include "arithmetic_type_strong.h"
#include "../convertor.h"

namespace PPreflection
{
	constexpr convertor_object make_numeric_conversion(PP::concepts::type auto t_this, const arithmetic_type& target)
	{
		auto type_to_convertor = PP::functor([t_this]
			(PP::concepts::type auto t)
			{
				return create_convertor_object(t_this, PP::value<[]
					(auto&& x)
					{
						return (PP_GET_TYPE(t))x;
					}>);
			});

		auto convertors = type_to_convertor < PP::arithmetic_types;

		auto type_index = PP::tuple_find_dynamic([&target]
			([[maybe_unused]] PP::concepts::type auto t)
			{
				return dynamic_cast<const arithmetic_type_strong<PP_GET_TYPE(t)>*>(&target) != nullptr;
			}, PP::arithmetic_types);

		return convertors[type_index];
	}
}
