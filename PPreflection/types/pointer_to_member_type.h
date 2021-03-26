#pragma once
#include "non_array_object_type.h"
#include "non_user_defined_type.h"

namespace PPreflection
{
	class class_type;

	class pointer_to_member_type : public detail::non_user_defined_type<non_array_object_type>
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

		constexpr virtual convertor_object bool_conversion() const noexcept = 0;
		constexpr virtual convertor_object member_function_noexcept_conversion() const noexcept = 0;
		constexpr virtual convertor_object base_pointer_conversion(const class_type& base) const noexcept = 0;
		
		constexpr standard_conversion_sequence make_standard_conversion_sequence(const pointer_to_member_type& target) const noexcept;
		constexpr standard_conversion_sequence make_standard_conversion_sequence(const non_array_object_type& target) const noexcept override final;
	};
}
