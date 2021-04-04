#pragma once
#include "convertor.h"

#include "PP/construct_pack.hpp"

#include "dynamic_reference.h"
#include "dynamic_variable.h"

namespace PPreflection::detail
{
	constexpr auto create_convertor_helper(PP::concepts::value auto ff, PP::concepts::type auto t, PP::concepts::value auto f)
	{
		return []
			(PPreflection::dynamic_reference ref)
			{
				return PP_GET_VALUE(ff)([ref]
					() -> decltype(auto)
					{
						return ref.visit(PP_COPY_TYPE(t), PP_GET_VALUE(f));
					});
			};
	}
}

constexpr PPreflection::convertor_reference PPreflection::create_convertor_reference(PP::concepts::type auto t, PP::concepts::value auto f) noexcept
{
	return detail::create_convertor_helper(PP::value<PP::construct_pack * PP::type<dynamic_reference>>, t, f);
}

constexpr PPreflection::convertor_object PPreflection::create_convertor_object(PP::concepts::type auto t, PP::concepts::value auto f) noexcept
{
	return detail::create_convertor_helper(PP::value<PP::construct_pack * PP::type<dynamic_object>>, t, f);
}
