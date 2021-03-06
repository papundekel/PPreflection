#pragma once
#include "convertor.h"

#include "dynamic_reference.h"
#include "dynamic_variable.h"

namespace
{
	constexpr auto create_convertor_helper(PP::concepts::value auto ff, PP::concepts::type auto t, PP::concepts::value auto f) noexcept
	{
		return []
			(PPreflection::dynamic_reference ref)
			{
				return PP_GET_VALUE(ff)([ref]
					()
					{
						return ref.visit(PP_COPY_TYPE(t), PP_GET_VALUE(f));
					});
			};
	}
}

constexpr PPreflection::convertor PPreflection::create_convertor(PP::concepts::type auto t, PP::concepts::value auto f) noexcept
{
	return create_convertor_helper(PP::value<[]
		(auto x)
		{
			return dynamic_variable::create(x);
		}>, t, f);
}
constexpr PPreflection::convertor_object PPreflection::create_convertor_object(PP::concepts::type auto t, PP::concepts::value auto f) noexcept
{
	return create_convertor_helper(PP::value<[]
		(auto x)
		{
			return dynamic_object(x);
		}>, t, f);
}
