#pragma once
#include "../../dynamic_variable.h"
#include "../../reflect.h"
#include "../constructor.h"
#include "../one_parameter_converting_constructor.h"
#include "apply_template.hpp"
#include "basic_function.h"
#include "concepts/constructible.hpp"
#include "concepts/destructible.hpp"
#include "conditional.hpp"
#include "construct_pack.hpp"
#include "functional/apply_partially.hpp"
#include "get_type.hpp"
#include "make_function_type.hpp"
#include "tuple_split.hpp"
#include "type_tuple.hpp"

namespace PPreflection::detail
{
	template <typename Class, typename Base, typename... Parameters>
	using basic_constructor_base_base = PP_GET_TYPE(PP::Template<basic_function>(
		PP::make_function_type_no_cvref(PP::type<Class(Parameters...)>, PP::value<PP::concepts::constructible_noexcept<Class, Parameters...>>),
		PP::type<Base>));

	template <typename Class, typename Base, typename... Parameters>
	class basic_constructor_base : public basic_constructor_base_base<Class, Base, Parameters...>
	{
		constexpr const overloaded_constructor& get_overloaded_function() const noexcept override final
		{
			return reflect(PP::type<tags::constructors<Class>>);
		}
	};

	template <typename Class, typename... Parameters>
	class basic_constructor_general final
		: public basic_constructor_base<Class, constructor, Parameters...>
	{
		dynamic_variable invoke_unsafe(PP::any_iterator<PP::iterator_category::ra, const dynamic_reference&> arg_iterator) const noexcept override final
		{
			if constexpr (PP::concepts::destructible<Class>)
				return this->invoke_helper(PP::construct_pack * PP::type<Class>, arg_iterator, this->parameter_types);
			else
				return dynamic_variable::create_invalid(dynamic_object::invalid_code::indestructible_return_value);
		}

		constexpr bool is_explicit() const noexcept override final
		{
			return reflect(PP::type<tags::is_explicit<Class, Parameters...>>);
		}
	};

	template <typename Class, typename Parameter>
	class basic_constructor_opc final
		: public basic_constructor_base<Class, one_parameter_converting_constructor, Parameter>
	{
		dynamic_variable invoke_unsafe_one_parameter(dynamic_reference arg) const noexcept override final
		{
			return dynamic_variable::create([arg]() { return Class(arg.cast_unsafe(PP::type<Parameter>)); });
		}

		constexpr const type& get_parameter_type() const noexcept override final
		{
			return type::reflect(PP::type<Parameter>);
		}
	};

	template <typename Class, typename... Parameters>
	using basic_constructor = PP_GET_TYPE(([](PP::concepts::type auto class_type, PP::concepts::type auto... parameter_types)
		{
			return [class_type, parameter_types...]
			{
				return conditional(PP_SIZEOF___(parameter_types) != PP::value_1 || reflect(PP::Template<tags::is_explicit>(class_type, parameter_types...)),
					PP::Template<basic_constructor_general>,
					PP::Template<basic_constructor_opc>);
			}()(class_type, parameter_types...);
		}(PP::type<Class>, PP::type<Parameters>...)));
}
