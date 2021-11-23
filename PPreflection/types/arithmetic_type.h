#pragma once
#include "../convertor.h"
#include "non_void_fundamental_type.h"

namespace PPreflection
{
///
/// @brief Represents an arithmetic type.
///
class arithmetic_type : public non_void_fundamental_type
{
public:
	///
	/// @brief Gets the promoted type.
	///
	constexpr virtual const arithmetic_type& promoted_type() const noexcept = 0;

private:
	constexpr virtual convertor_object conversion(
		const arithmetic_type& target) const noexcept = 0;

	constexpr detail::standard_conversion_sequence
	make_standard_conversion_sequence_impl(
		const non_array_object_type& target) const noexcept override final;
};
}
