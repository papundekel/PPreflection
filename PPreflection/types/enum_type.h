#pragma once
#include "PP/any_view.hpp"

#include "../named_descriptor.h"
#include "user_defined_type.h"

namespace PPreflection
{
class enum_type;
class dynamic_object;

///
/// @brief Represents an enum value.
///
class enum_value : public named_descriptor<descriptor>
{
public:
	///
	/// @brief Get the value as a dynamic object
	///
	constexpr virtual dynamic_object get_value() const noexcept = 0;

	///
	/// @brief Gets the associated enum.
	///
	constexpr virtual const enum_type& get_parent() const noexcept = 0;

private:
	constexpr virtual void print_name_before_parent(PP::ostream&) const noexcept
	{}

	constexpr virtual void print_name_after_parent(
		PP::ostream& out) const noexcept
	{
		out.write(get_name());
		// out.write(" = ");
		// out.write(get_value());
	}

	constexpr parent_descriptor get_parent(void*) const noexcept override final
	{
		return {};
	}
};

///
/// @brief Represents an enum type.
///
class enum_type : public user_defined_type
{
public:
	///
	/// @brief Gets a view of possible values.
	///
	constexpr virtual PP::any_view<PP::iterator_category::ra, const enum_value&>
	get_values() const noexcept = 0;

	///
	/// @brief Gets the underlying integral type.
	///
	constexpr virtual const integral_type& get_underlying_type()
		const noexcept = 0;

	///
	/// @brief Return whether the enum is scoped.
	///
	constexpr virtual bool is_scoped() const noexcept = 0;

	///
	/// @brief Return whether the enum has the underlying type fixed.
	///
	constexpr virtual bool has_fixed_underlying_type() const noexcept = 0;

	constexpr void destroy(void*) const noexcept override final
	{}

private:
	constexpr virtual convertor_object conversion(
		const arithmetic_type& target) const noexcept = 0;

	constexpr detail::standard_conversion_sequence
	make_standard_conversion_sequence_impl(
		const non_array_object_type& target) const noexcept override final;
};
}
