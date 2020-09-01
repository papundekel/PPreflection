#pragma once
#include <type_traits>
#include "basic_function.h"
#include "apply_pack.h"
#include "reflect.h"
#include "overloaded_constructor.h"
#include "constructor.h"

namespace detail
{
	template <typename Class>
	struct is_nothrow_constructible_helper
	{
		template <typename... Args>
		using help = value_t<std::is_nothrow_constructible_v<Class, Args...>>;
	};

	template <typename Class, bool Explicit, typename Args>
	class basic_class_constructor :
		public basic_function
		< detail::constructor_wrap<Class>
		, Args
		, Class
		, get_value<apply_pack<is_nothrow_constructible_helper<Class>::template help, Args>>()
		, constructor>
	{
	protected:
		constexpr void invoke_implementation(void* result, const dynamic_reference* args) const noexcept override final
		{
			new (result) Class(get_value<apply_pack<function::invoke_helper_t, Args>>()(
				[]<typename... T>(T&&... xs)
			{
				return Class(std::forward<T>(xs)...);
			}, args));
		}

	public:
		constexpr bool is_explicit() const noexcept override final
		{
			return Explicit;
		}

		constexpr const type& get_enclosing_class() const noexcept override final
		{
			return reflect<Class, type>();
		}
	};
}
