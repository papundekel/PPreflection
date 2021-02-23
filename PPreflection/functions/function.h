#pragma once
#include "../descriptor.h"
#include "../dynamic_variable.h"
#include "../types/function_type.h"
#include "../types/return_type_reference.h"
#include "any_iterator.hpp"
#include "functional/id.hpp"
#include "transform_view.hpp"
#include "tuple_value_sequence_for.hpp"
#include "tuple_zip_with.hpp"
#include "type_tuple.hpp"
#include "utility/forward.hpp"
#include "view_tuple.hpp"

namespace PPreflection
{
	class type;
	class dynamic_reference;
	class member_function;
	class overloaded_function;

	class function : public descriptor
	{
		friend overloaded_function;

	protected:
		constexpr virtual dynamic_variable invoke_unsafe(PP::any_iterator<PP::iterator_category::ra, const dynamic_reference&> arg_iterator) const noexcept = 0;

		constexpr virtual bool can_invoke(PP::any_view<PP::iterator_category::ra, const reference_type&> argument_types) const noexcept;

		static inline dynamic_variable invoke_helper(auto&& f, PP::any_iterator<PP::iterator_category::ra, const dynamic_reference&> arg_iterator, auto parameter_types) noexcept
		{
			/*return dynamic_variable::create(
				[&f, arg_iterator, parameter_types]() -> decltype(auto)
				{
					return PP::tuple_apply(PP_FORWARD(f), PP::tuple_zip_with(
						[](auto ref, auto t) -> decltype(auto)
						{
							return ref.cast_unsafe(t);
						}, std::make_pair(PP::concepts::view_tuple(arg_iterator), parameter_types)));
				});*/

			return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
		}

		constexpr void print_name_basic(PP::simple_ostream& out) const noexcept;
		constexpr void print_noexcept(PP::simple_ostream& out) const noexcept;

		constexpr void print_name_before_parent(PP::simple_ostream& out) const noexcept override final;
		constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override;

	public:
		constexpr bool has_name(PP::string_view name) const noexcept override;

		constexpr virtual const function_type& get_function_type() const noexcept = 0;
		constexpr return_type_reference return_type() const noexcept
		{
			return get_function_type().return_type();
		}
		constexpr auto parameter_types() const noexcept
		{
			return get_function_type().parameter_types();
		}

		constexpr bool is_noexcept() const noexcept
		{
			return get_function_type().is_noexcept();
		}

		inline dynamic_variable invoke(PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args = {}) const;

		constexpr virtual const overloaded_function& get_overloaded_function() const noexcept = 0;

		constexpr const descriptor& get_parent() const noexcept override;

		using overloaded = overloaded_function;
	};

	class overloaded_function : public descriptor
	{
	protected:
		constexpr virtual PP::any_view<PP::iterator_category::ra, const function&> get_function_overloads() const noexcept = 0;

	public:
		constexpr virtual void print_name_before_parent(PP::simple_ostream& out) const noexcept override final
		{}

		inline dynamic_variable invoke(PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args = {}) const;

		constexpr const function* select_overload(PP::concepts::view auto&& argument_types) const noexcept
		{
			for (const function& f : get_overloads())
				if (f.can_invoke(PP_FORWARD(argument_types)))
					return &f;

			return nullptr;
		}

		constexpr auto get_overloads() const noexcept
		{
			return get_function_overloads();
		}
	};

	constexpr const descriptor& function::get_parent() const noexcept
	{
		return get_overloaded_function().get_parent();
	}
}
