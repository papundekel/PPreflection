#pragma once
#include <type_traits>
#include "basic_function.h"
#include "apply_pack.h"
#include "reflect.h"
#include "overloaded_constructor.h"
#include "constructor.h"
#include "one_parameter_converting_constructor.h"

namespace detail
{
	template <typename Class>
	struct is_nothrow_constructible_helper
	{
		template <typename... Args>
		using help = value_t<std::is_nothrow_constructible_v<Class, Args...>>;
	};

	template <typename Class, typename Args, typename Base>
	using basic_constructor_base
		= basic_function
			< constructor_wrap<Class>
			, Args
			, Class
			, get_value<apply_pack<is_nothrow_constructible_helper<Class>::template help, Args>>()
			, Base>;

	template <typename Class, bool Explicit, typename Args>
	class basic_class_constructor final
		: public basic_constructor_base<Class, Args, constructor>
	{
	protected:
		constexpr dynamic_object invoke_unsafe(any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final
		{
			return invoke_helper<Class, Args>(
				[]<typename... T>(T&&... xs)
				{
					return Class(std::forward<T>(xs)...);
				}, arg_iterator);
		}

	public:
		constexpr bool is_explicit() const noexcept override final
		{
			return Explicit;
		}
	};

	template <typename Class, typename Arg>
	class basic_class_constructor<Class, false, type_pack<Arg>> final
		: public basic_constructor_base<Class, type_pack<Arg>, one_parameter_converting_constructor>
	{
	protected:
		constexpr dynamic_object invoke_unsafe_one_parameter(dynamic_reference arg) const noexcept override final
		{
			return dynamic_object::create<Class>(arg.cast_unsafe<Arg>());
		}
	public:
		constexpr const type& get_parameter_type() const noexcept override final
		{
			return reflect<Arg, type>();
		}
	};
}
