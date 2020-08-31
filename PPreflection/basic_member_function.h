#pragma once
#include "member_function.h"
#include "get_member_function_info.h"
#include "get_function_info.h"
#include "basic_typed_function.h"

namespace detail
{
	template <typename Overload, auto mf>
	using basic_member_function_base = basic_typed_function<Overload, typename get_member_function_info<decltype(mf)>::function_type, member_function>;

	template <typename Overload, auto mf>
	class basic_member_function : public basic_member_function_base<Overload, mf>
	{
		using B = basic_member_function_base<Overload, mf>;
		using FunctionType = typename B::FunctionType;
		using ParentClass = typename get_member_function_info<decltype(mf)>::class_;
		using CallerParameterType = typename get_member_function_info<decltype(mf)>::caller_type;

	protected:
		constexpr void invoke_implementation_member(void* result, const dynamic_reference& caller, const dynamic_reference* args) const noexcept override final
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

		constexpr const type& get_enclosing_class() const noexcept override final
		{
			return reflect<ParentClass, type>();
		}

		constexpr const overloaded_member_function& get_overloaded_function() const noexcept override final
		{
			return reflect<Overload, overloaded_member_function>();
		}
	};
}
