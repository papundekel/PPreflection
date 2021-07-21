#pragma once
#include "class_type.h"

namespace PPreflection::detail
{
class initialization;
}

namespace PPreflection
{
class function_type;
class pointer_type;

///
/// @brief Represents a non-union class type.
///
class non_union_class_type : public class_type
{
	friend function_type;
	friend detail::initialization;
	friend pointer_type;
	friend dynamic_reference dynamic_polymorphic_reference(auto&&);

public:
	///
	/// @brief Gets a view of all base classes.
	///
	constexpr virtual PP::any_view<PP::iterator_category::ra,
	                               const non_union_class_type&>
	get_base_classes() const noexcept = 0;

	constexpr const non_union_class_type* as_non_union_class()
		const noexcept override final
	{
		return this;
	}

private:
	constexpr virtual convertor_object pointer_conversion_to_base(
		const non_union_class_type& base) const noexcept = 0;

	constexpr virtual convertor_reference reference_conversion_to_base(
		const non_union_class_type& base) const noexcept = 0;
	constexpr virtual convertor_reference reference_conversion_to_derived(
		const non_union_class_type& base) const noexcept = 0;
};
}
