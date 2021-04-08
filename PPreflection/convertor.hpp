#pragma once
#include "convertor.h"

#include "PP/construct_pack.hpp"
#include "PP/functional/compose.hpp"

#include "dynamic_object.h"
#include "dynamic_reference.h"

namespace PPreflection::detail
{
	constexpr auto create_convertor_helper(PP::concepts::value auto ff, PP::concepts::type auto t, PP::concepts::value auto f)
	{
		return []
			(PPreflection::dynamic_reference ref)
			{
				return ref.visit(PP_COPY_TYPE(t), PP::compose(PP_GET_VALUE(ff), PP_GET_VALUE(f)));
			};
	}
}

constexpr PPreflection::convertor_reference PPreflection::create_convertor_reference(PP::concepts::type auto t, PP::concepts::value auto f) noexcept
{
	return detail::create_convertor_helper(PP::value<PP::construct_pack * PP::type<dynamic_reference>>, t, f);
}

constexpr PPreflection::convertor_object PPreflection::create_convertor_object(PP::concepts::type auto t, PP::concepts::value auto f) noexcept
{
	return detail::create_convertor_helper(PP::value<[](auto x){ return dynamic_object::create(PP_DECLTYPE(x), x); }>, t, f);
}
