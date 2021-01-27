#pragma once
#include <type_traits>
#include "basic_function.h"
#include "../../reflect.h"
#include "../constructor.h"
#include "../one_parameter_converting_constructor.h"
#include "make_function_type.hpp"
#include "../../dynamic_variable.h"
#include "functional/construct.hpp"
#include "get_type.hpp"
#include "tuple_split.hpp"
#include "type_tuple.hpp"
#include "conditional.hpp"
#include "add_function_cvrefn.hpp"

namespace detail
{
	template <typename Class, typename Base, typename... Parameters>
	using basic_constructor_base_base = basic_function<
		PP::get_v_type<PP::add_function_cvrefn(PP::type<Class(Parameters...)>, PP::value<std::is_nothrow_constructible_v<Class, Parameters...>>)>,
		Base>;

	template <typename Class, typename Base, typename... Parameters>
	class basic_constructor_base : public basic_constructor_base_base<Class, Base, Parameters...>
	{
		constexpr const overloaded_constructor& get_overloaded_function() const noexcept override final
		{
			return reflect(PP::type<reflection::constructors<Class>>);
		}
	};

	template <typename Class, typename... Parameters>
	class basic_constructor_general final
		: public basic_constructor_base<Class, constructor, Parameters...>
	{
		dynamic_variable invoke_unsafe(PP::any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final
		{
			if constexpr (std::is_destructible_v<Class>)
				return this->invoke_helper(PP::construct(PP::type<Class>), arg_iterator, this->parameter_types);
			else
				return dynamic_variable::create_invalid(dynamic_object::invalid_code::indestructible_return_value);
		}

		constexpr bool is_explicit() const noexcept override final
		{
			return reflect(PP::type<reflection::is_explicit<Class, Parameters...>>);
		}
	};

	template <typename Class, typename Parameter>
	class basic_constructor_opc final
		: public basic_constructor_base<Class, one_parameter_converting_constructor, Parameter>
	{
		dynamic_variable invoke_unsafe_one_parameter(dynamic_reference arg) const noexcept override final
		{
			return dynamic_variable::create([arg]() { return Class(arg.cast_unsafe<Parameter>()); });
		}

		constexpr const type& get_parameter_type() const noexcept override final
		{
			return type::reflect(PP::type<Parameter>);
		}
	};

	template <typename Class, typename... Parameters>
	constexpr inline auto basic_constructor_helper = PP::type<basic_constructor_general<Class, Parameters...>>;

	template <typename Class, typename Parameter>
	constexpr inline auto basic_constructor_helper<Class, Parameter> =
		PP::conditional(
			PP::value<reflect(PP::type<reflection::is_explicit<Class, Parameter>>)>,
			PP::type<basic_constructor_general<Class, Parameter>>,
			PP::type<basic_constructor_opc<Class, Parameter>>);

	template <typename Class, typename... Parameters>
	using basic_constructor = PP::get_v_type<basic_constructor_helper<Class, Parameters...>>;
}
