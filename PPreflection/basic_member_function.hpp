#pragma once
#include <type_traits>
#include "basic_member_function.h"
#include "member_function.h"
#include "type.h"
#include "get_function_info.h"
#include "get_value.h"
#include "basic_function.h"
#include "overloaded_function.h"

template <typename Overload, auto mf>
constexpr void detail::basic_member_function<Overload, mf>::invoke_implementation_member(void* result, const dynamic_reference& caller, const dynamic_reference* args) const noexcept
{
	this->invoke_(result,
		[&caller, args]()
		{
			return get_value<apply_pack<function::invoke_helper_t, typename B::ParameterTypes>>()(
				[&caller]<typename... T>(T&&... xs)
				{
					return (caller.cast_unsafe<CallerParameterType>().*mf)(std::forward<T>(xs)...);
				}, args);
		});
}

template <typename Overload, auto mf>
constexpr const type& detail::basic_member_function<Overload, mf>::get_pointer_type() const noexcept
{
	return reflect<decltype(mf), type>();
}
template <typename Overload, auto mf>
constexpr const type& detail::basic_member_function<Overload, mf>::get_caller_parameter_type() const noexcept
{
	return reflect<CallerParameterType, type>();
}
template <typename Overload, auto mf>
constexpr ref_qualifier detail::basic_member_function<Overload, mf>::get_ref_qualifier() const noexcept
{
	return get_function_info<FunctionType>::ref;
}
template <typename Overload, auto mf>
constexpr cv_qualifier detail::basic_member_function<Overload, mf>::get_cv_qualifier() const noexcept
{
	return get_function_info<FunctionType>::cv;
}
template <typename Overload, auto mf>
constexpr const type& detail::basic_member_function<Overload, mf>::get_enclosing_class() const noexcept
{
	return reflect<ParentClass, type>();
}
template <typename Overload, auto mf>
constexpr const overloaded_member_function& detail::basic_member_function<Overload, mf>::get_overloaded_function() const noexcept
{
	return reflect<Overload, overloaded_member_function>();
}
