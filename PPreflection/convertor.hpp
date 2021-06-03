#pragma once
#include "convertor.h"

#include "PP/construct_pack.hpp"
#include "PP/functional/compose.hpp"

#include "dynamic_object.h"
#include "dynamic_reference.hpp"

constexpr PPreflection::convertor_reference
PPreflection::create_convertor_reference(PP::concepts::type auto t,
										 PP::concepts::value auto f) noexcept
{
	return [](PPreflection::dynamic_reference ref)
	{
		return ref.visit(
			PP_COPY_TYPE(t),
			PP::compose(PP::construct_pack * PP::type<dynamic_reference>,
						PP_GET_VALUE(f)));
	};
}

constexpr PPreflection::convertor_object PPreflection::create_convertor_object(
	PP::concepts::type auto t,
	PP::concepts::value auto f) noexcept
{
	return [](PPreflection::dynamic_reference ref)
	{
		return ref.visit(PP_COPY_TYPE(t),
						 [](auto&& value)
						 {
							 return dynamic_object(
								 [&value]()
								 {
									 return PP_GET_VALUE(f)(PP_FORWARD(value));
								 });
						 });
	};
}
