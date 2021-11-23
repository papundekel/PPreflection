#pragma once
#include "array_type.h"
#include "object_type.h"

namespace PPreflection
{
	///
	/// @brief Represent an unbounded array type.
	///
	class unknown_bound_array_type : public detail::array_type<object_type>
	{
	public:
		///
		/// @brief Compares two unbounded array types.
		///
		constexpr bool operator==(
			const unknown_bound_array_type& other) const noexcept;

		constexpr bool has_name(PP::string_view) const noexcept override final
		{
			return true;
		}

		constexpr bool operator==(
			const type& other) const noexcept override final
		{
			return compare(*this, other);
		}

	private:
		constexpr void print_name_prefix(
			PP::ostream& out) const noexcept override final
		{
			remove_extent().print_name_prefix(out);
		}
		constexpr void print_name_suffix(
			PP::ostream& out) const noexcept override final
		{
			out.write("[]");
			remove_extent().print_name_suffix(out);
		}
		constexpr PP::variant<const unknown_bound_array_type&,
		                      const complete_object_type&>
			cast_down(
				PP::overload_tag<object_type>) const noexcept override final
		{
			return {PP::placeholder, *this};
		}
	};
}
