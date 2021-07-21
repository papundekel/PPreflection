#pragma once
#include "../types/function_type.h"
#include "maybe_static_member_function.h"

namespace PPreflection
{
class class_type;
class reference_type;

///
/// @brief Represents a member function.
///
class member_function : public maybe_static_member_function
{
public:
	///
	/// @brief Gets the ref qualifier of the function.
	///
	constexpr PP::ref_qualifier get_ref_qualifier() const noexcept
	{
		return get_function_type().get_function_ref_qualifier();
	}

	///
	/// @brief Gets the cv qualifier of the function.
	///
	constexpr PP::cv_qualifier get_cv_qualifier() const noexcept
	{
		return get_function_type().get_function_cv_qualifier();
	}

	constexpr void print_name_after_parent(
		PP::ostream& out) const noexcept override final;

private:
	virtual dynamic_variable invoke_unsafe(
		dynamic_reference caller,
		PP::any_iterator<PP::iterator_category::ra, dynamic_reference>
			arg_iterator) const = 0;

	dynamic_variable invoke_unsafe(
		PP::any_iterator<PP::iterator_category::ra, dynamic_reference>
			arg_iterator,
		void*) const override final;
};
}
