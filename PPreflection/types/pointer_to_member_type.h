#pragma once
#include "non_user_defined_type.h"
#include "pointer_base_type.h"

namespace PPreflection
{
	class non_union_class_type;

	class pointer_to_member_type : public detail::non_user_defined_type<pointer_base_type>
	{
	public:
		constexpr PP::type_disjunction_reference<
			non_void_fundamental_type,
			pointer_type,
			pointer_to_member_type,
			user_defined_type> cast_down(PP::overload_tag<non_array_object_type>) const noexcept override final
		{
			return *this;
		}

		constexpr virtual const class_type& get_class_type() const noexcept = 0;
		constexpr virtual cv_type<referencable_type> get_member_type() const noexcept = 0;

		constexpr bool operator==(const pointer_to_member_type& other) const noexcept;
		constexpr bool operator==(const type& other) const noexcept override final
		{
			return compare(*this, other);
		}

		constexpr virtual convertor_object member_function_noexcept_conversion() const noexcept = 0;
		constexpr virtual convertor_object base_pointer_conversion(const non_union_class_type& derived) const noexcept = 0;
		
		constexpr standard_conversion_sequence make_standard_conversion_sequence(const pointer_to_member_type& target) const noexcept;
		constexpr standard_conversion_sequence make_standard_conversion_sequence(const non_array_object_type& target) const noexcept override final;
	};
}
