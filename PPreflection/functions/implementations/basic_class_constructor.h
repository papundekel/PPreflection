#pragma once
#include <type_traits>
#include "basic_function.h"
#include "apply_pack.hpp"
#include "../../reflect.h"
#include "../constructor.h"
#include "../one_parameter_converting_constructor.h"
#include "make_function_type.hpp"

namespace detail
{
	template <typename Class>
	struct is_nothrow_constructible_helper
	{
		template <typename... Args>
		using help = PP::value_t<std::is_nothrow_constructible_v<Class, Args...>>;
	};

	template <typename Class, typename Args, typename Base>
	using basic_constructor_base_base = basic_function
		< constructor_wrap<Class>
		, Args
		, Class
		, PP::get_value<PP::apply_pack<is_nothrow_constructible_helper<Class>::template help, Args>>()
		, Base>;

	template <typename Class, typename Args, typename Base>
	class basic_constructor_base : public basic_constructor_base_base<Class, Args, Base>
	{
		using B = basic_constructor_base_base<Class, Args, Base>;

		constexpr const function_type& get_function_type() const noexcept override final
		{
			return type::reflect<PP::make_function_type<Class, Args, B::Noexcept>>();
		}
	};

	template <typename Class, bool Explicit, typename Args>
	class basic_class_constructor final
		: public basic_constructor_base<Class, Args, constructor>
	{
	protected:
		inline dynamic_variable invoke_unsafe(PP::any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final
		{
			return invoke_helper<Args>(
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
	class basic_class_constructor<Class, false, PP::type_pack<Arg>> final
		: public basic_constructor_base<Class, PP::type_pack<Arg>, one_parameter_converting_constructor>
	{
	protected:
		inline dynamic_variable invoke_unsafe_one_parameter(dynamic_reference arg) const noexcept override final
		{
			return dynamic_variable::create([arg]() { return Class(arg.cast_unsafe<Arg>()); });
		}
	public:
		constexpr const type& get_parameter_type() const noexcept override final
		{
			return type::reflect<Arg>();
		}
	};
}
