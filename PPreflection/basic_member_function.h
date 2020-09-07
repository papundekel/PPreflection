#pragma once
#include "member_function.h"
#include "get_member_function_info.h"
#include "get_function_info.h"
#include "basic_typed_function.h"

namespace detail
{
	template <typename Overload, auto mf, typename Base>
	using basic_member_function_helper = basic_typed_function<Overload, typename get_member_function_info<decltype(mf)>::Function, Base>;

	template <typename Overload, auto mf, typename Base>
	class basic_member_function_base : public basic_member_function_helper<Overload, mf, Base>
	{
	protected:
		using B = basic_member_function_helper<Overload, mf, Base>;
		using FunctionType = B::FunctionType;
		//using ParentClass = typename get_member_function_info<decltype(mf)>::Class;
		using CallerParameterType = typename get_member_function_info<decltype(mf)>::caller_type;

		constexpr const type& get_pointer_type() const noexcept override final
		{
			return reflect<decltype(mf), type>();
		}
		
		constexpr const type& get_caller_parameter_type() const noexcept override final
		{
			return reflect<CallerParameterType, type>();
		}

	public:
		constexpr ref_qualifier get_ref_qualifier() const noexcept override final
		{
			return get_function_info<FunctionType>::ref;
		}
		constexpr cv_qualifier get_cv_qualifier() const noexcept override final
		{
			return get_function_info<FunctionType>::cv;
		}
	};

	template <typename Overload, auto mf>
	class basic_member_function : public basic_member_function_base<Overload, mf, member_function>
	{
		using B = basic_member_function_base<Overload, mf, member_function>;
		using ReturnType = typename B::ReturnType;
		using ParameterTypes = typename B::ParameterTypes;

	protected:
		constexpr dynamic_object invoke_unsafe_member(dynamic_reference caller, any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final
		{
			return invoke_helper<ReturnType, ParameterTypes>(
				[caller]<typename... T>(T&&... xs) -> decltype(auto)
				{
					return (caller.cast_unsafe<typename B::CallerParameterType>().*mf)(std::forward<T>(xs)...);
				}, arg_iterator);
		}
	};
}
