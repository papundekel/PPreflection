#pragma once
#include "PP/variant.hpp"

#include "known_bound_array_type.h"
#include "unknown_bound_array_type.h"

namespace PPreflection
{
	namespace detail
	{
		using array_type_reference_helper =
			PP::variant<const known_bound_array_type&,
						const unknown_bound_array_type&>;
	}

	class array_type_reference
		: public detail::array_type_reference_helper
		, public detail::array_type<object_type>
	{
	public:
		using detail::array_type_reference_helper::array_type_reference_helper;

	private:
		static constexpr array_type_reference create(const object_type& t)
		{
			if (auto known_bound =
					dynamic_cast<const known_bound_array_type*>(&t);
				known_bound)
				return array_type_reference(*known_bound);
			else
				return array_type_reference(
					dynamic_cast<const unknown_bound_array_type&>(t));
		}

		constexpr PP::variant<const unknown_bound_array_type&,
							  const complete_object_type&>
			cast_down(
				PP::overload_tag<object_type>) const noexcept override final
		{
			using RET = PP::variant<const unknown_bound_array_type&,
									const complete_object_type&>;

			return PP::visit(PP::overloaded(
								 [](const unknown_bound_array_type& t)
								 {
									 return RET(PP::placeholder, t);
								 },
								 [](const known_bound_array_type& t)
								 {
									 return RET(PP::placeholder, t);
								 }),
							 *this);
		}

	public:
		constexpr array_type_reference(const object_type& t) noexcept
			: array_type_reference(create(t))
		{}

		constexpr bool has_name(
			PP::string_view name) const noexcept override final
		{
			return PP::visit(
				[name](const auto& array_type)
				{
					return array_type.has_name(name);
				},
				*this);
		}

		constexpr void print_name_prefix(
			PP::simple_ostream& out) const noexcept override final
		{
			PP::visit(
				[&out](const auto& array_type)
				{
					array_type.print_name_prefix(out);
				},
				*this);
		}

		constexpr void print_name_suffix(
			PP::simple_ostream& out) const noexcept override final
		{
			PP::visit(
				[&out](const auto& array_type)
				{
					array_type.print_name_suffix(out);
				},
				*this);
		}

		constexpr cv_type<complete_object_type> remove_extent()
			const noexcept override final
		{
			return PP::visit(
				[](const auto& array_type)
				{
					return array_type.remove_extent();
				},
				*this);
		}

		constexpr convertor_object array_to_pointer_conversion()
			const noexcept override final
		{
			return PP::visit(
				[](const auto& array_type)
				{
					return array_type.array_to_pointer_conversion();
				},
				*this);
		}

		constexpr bool operator==(
			const type& other) const noexcept override final
		{
			return PP::visit(
				[&other](const auto& array_type)
				{
					return array_type == other;
				},
				*this);
		}

		constexpr const pointer_type& get_pointer_to_element()
			const noexcept override final
		{
			return PP::visit(
				[](const auto& array_type) -> auto&
				{
					return array_type.get_pointer_to_element();
				},
				*this);
		}
	};
}
