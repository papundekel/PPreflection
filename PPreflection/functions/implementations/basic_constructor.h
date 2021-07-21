#pragma once
#include "PP/apply_partially.hpp"
#include "PP/apply_template.hpp"
#include "PP/concepts/constructible.hpp"
#include "PP/concepts/destructible.hpp"
#include "PP/conditional.hpp"
#include "PP/construct_pack.hpp"
#include "PP/get_type.hpp"
#include "PP/make_function_type.hpp"
#include "PP/tuple_split.hpp"
#include "PP/type_tuple.hpp"

#include "../../dynamic_variable.h"
#include "../../reflect.h"
#include "../constructor.h"
#include "../one_parameter_converting_constructor.h"
#include "basic_function.h"

namespace PPreflection::detail
{
template <typename Class, typename Base, typename... Parameters>
using basic_constructor_base_base = PP_GT(PP::Template<basic_function>(
	PP::make_function_type(
		PP::type<Class(Parameters...)>,
		PP::value<PP::concepts::constructible_noexcept<Class, Parameters...>>),
	PP::type<Base>));

template <typename Class, typename Base, typename... Parameters>
class basic_constructor_base
	: public basic_constructor_base_base<Class, Base, Parameters...>
{
	constexpr const class_type& get_parent() const noexcept override final
	{
		return type::reflect(PP::type<Class>);
	}
};

template <typename Class, typename... Parameters>
class basic_constructor_general final
	: public basic_constructor_base<Class, constructor, Parameters...>
{
	dynamic_object invoke_unsafe(
		PP::any_iterator<PP::iterator_category::ra, dynamic_reference>
			arg_iterator) const noexcept override final
	{
		if constexpr (!PP::concepts::destructible<Class>)
			return dynamic_object::create_invalid(
				dynamic_object::invalid_code::indestructible_return_value);
		else if constexpr (!PP::concepts::constructible<Class, Parameters...>)
			return dynamic_object::create_invalid(
				dynamic_object::invalid_code::abstract_class);
		else
			return this->call_with_arguments_cast_to_parameter_types(
				[](auto&&... args)
				{
					return dynamic_object::create(PP::type<Class>,
				                                  PP_F(args)...);
				},
				PP::move(arg_iterator),
				this->parameter_types);
	}

	constexpr bool is_explicit() const noexcept override final
	{
		return reflect(PP::type<tags::is_explicit<Class, Parameters...>>);
	}
};

template <typename Class, typename Parameter>
class basic_constructor_opc final
	: public basic_constructor_base<Class,
                                    one_parameter_converting_constructor,
                                    Parameter>
{
	dynamic_object invoke_unsafe(
		dynamic_reference arg) const noexcept override final
	{
		if constexpr (!PP::concepts::destructible<Class>)
			return dynamic_object::create_invalid(
				dynamic_object::invalid_code::indestructible_return_value);
		else if constexpr (!PP::concepts::constructible<Class, Parameter>)
			return dynamic_object::create_invalid(
				dynamic_object::invalid_code::abstract_class);
		else
			return dynamic_object::create(PP::type<Class>,
			                              arg.cast_unsafe(PP::type<Parameter>));
	}

	constexpr parameter_type get_parameter_type() const noexcept override final
	{
		return type::reflect(PP::type<Parameter>);
	}
};

template <typename Class, typename... Parameters>
using basic_constructor = PP_GT((
	[](PP::concepts::type auto class_type,
       PP::concepts::type auto... parameter_types)
	{
		return [class_type, parameter_types...]
		{
			return PP::conditional(
				PP_SIZEOF___(parameter_types) != PP::value_1 ||
					reflect(
						PP::Template<tags::is_explicit>(class_type,
		                                                parameter_types...)),
				PP::Template<basic_constructor_general>,
				PP::Template<basic_constructor_opc>);
		}()(class_type, parameter_types...);
	}(PP::type<Class>, PP::type<Parameters>...)));
}
