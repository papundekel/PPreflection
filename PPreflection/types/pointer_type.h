#pragma once
#include "../convertor.h"
#include "non_user_defined_type.h"
#include "pointer_base_type.h"

namespace PPreflection
{
	template <typename>
	class cv_type;

	class pointer_type : public detail::non_user_defined_type<pointer_base_type>
	{
	public:
		constexpr PP::variant<const non_void_fundamental_type&,
		                      const pointer_type&,
		                      const pointer_to_member_type&,
		                      const user_defined_type&>
			cast_down(PP::overload_tag<non_array_object_type>)
				const noexcept override final
		{
			return {PP::placeholder, *this};
		}

		constexpr bool has_name(PP::string_view) const noexcept override final
		{
			return true;
		}
		constexpr void print_name_prefix(
			PP::ostream& out) const noexcept override final
		{
			remove_pointer().print_name_prefix(out);
			out.write("(*");
		}
		constexpr void print_name_suffix(
			PP::ostream& out) const noexcept override final
		{
			out.write(")");
			remove_pointer().print_name_suffix(out);
		}

		constexpr PP::size_t alignment() const noexcept override final
		{
			return alignof(void*);
		}
		constexpr PP::size_t size() const noexcept override final
		{
			return sizeof(void*);
		}
		constexpr void destroy(void*) const noexcept override final
		{}

		constexpr virtual cv_type<pointable_type> remove_pointer()
			const noexcept = 0;

		constexpr bool operator==(const pointer_type& other) const noexcept
		{
			return remove_pointer() == other.remove_pointer();
		}
		constexpr bool operator==(
			const type& other) const noexcept override final
		{
			return compare(*this, other);
		}

		constexpr virtual convertor_object void_conversion() const noexcept = 0;

		constexpr standard_conversion_sequence
		make_standard_conversion_sequence_impl(
			const pointer_type& target) const noexcept;
		constexpr standard_conversion_sequence
		make_standard_conversion_sequence_impl(
			const non_array_object_type& target) const noexcept override final;
	};
}
