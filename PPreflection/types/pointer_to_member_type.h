#pragma once
#include "non_user_defined_type.h"
#include "pointer_base_type.h"

namespace PPreflection
{
class non_union_class_type;

///
/// @brief Represents a pointer to member type.
///
class pointer_to_member_type
	: public detail::non_user_defined_type<detail::pointer_base_type::wrapped>
{
public:
	///
	/// @brief Gets the class type of the member.
	///
	constexpr virtual const class_type& get_class_type() const noexcept = 0;

	///
	/// @brief Gets the member cv qualified type.
	///
	constexpr virtual cv_type<referencable_type> get_member_type()
		const noexcept = 0;

	///
	/// @brief Compares two pointer to member types.
	///
	constexpr bool operator==(
		const pointer_to_member_type& other) const noexcept;

	constexpr bool operator==(const type& other) const noexcept override final
	{
		return compare(*this, other);
	}

private:
	constexpr PP::variant<const non_void_fundamental_type&,
	                      const pointer_type&,
	                      const pointer_to_member_type&,
	                      const user_defined_type&>
		cast_down(PP::overload_tag<non_array_object_type>)
			const noexcept override final
	{
		return {PP::placeholder, *this};
	}

	constexpr virtual convertor_object member_function_noexcept_conversion()
		const noexcept = 0;

	constexpr virtual convertor_object pointer_conversion_to_base(
		const non_union_class_type& derived) const noexcept = 0;

	constexpr detail::standard_conversion_sequence
	make_standard_conversion_sequence_impl(
		const pointer_to_member_type& target) const noexcept;

	constexpr detail::standard_conversion_sequence
	make_standard_conversion_sequence_impl(
		const non_array_object_type& target) const noexcept override final;
};
}
