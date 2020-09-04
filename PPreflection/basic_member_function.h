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

	protected:
		constexpr void invoke_implementation_member(void* result, dynamic_reference caller, const dynamic_reference* args) const noexcept override final
		{
			this->invoke_(result,
				[caller, args]() -> decltype(auto)
				{
					return get_value<apply_pack<function::invoke_helper_t, typename B::ParameterTypes>>()(
						[caller]<typename... T>(T&&... xs) -> decltype(auto)
					{
						return (caller.cast_unsafe<typename B::CallerParameterType>().*mf)(std::forward<T>(xs)...);
					}, args);
				});
		}
	};
}
