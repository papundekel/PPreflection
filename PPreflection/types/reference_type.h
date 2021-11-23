#pragma once
#include "non_user_defined_type.h"
#include "type.h"

namespace PPreflection
{
	template <typename>
	class cv_type;

	class referencable_type;

	///
	/// @brief Represents a reference type.
	///
	class reference_type : public detail::non_user_defined_type<type>
	{
	public:
		///
		/// @brief Gets the referenced cv qualified type.
		///
		constexpr virtual cv_type<referencable_type> remove_reference()
			const noexcept = 0;

		///
		/// @brief lvalue check.
		///
		/// @retval true iff is lvalue.
		///
		constexpr virtual bool is_lvalue() const noexcept = 0;

		///
		/// @brief Compares two reference types.
		///
		constexpr bool operator==(const reference_type& other) const noexcept;
		constexpr bool operator==(
			const type& other) const noexcept override final
		{
			return compare(*this, other);
		}

		constexpr bool has_name(PP::string_view) const noexcept override final
		{
			return true;
		}

	private:
		constexpr void print_name_prefix(
			PP::ostream& out) const noexcept override final;
		constexpr void print_name_suffix(
			PP::ostream& out) const noexcept override final;

		constexpr PP::variant<const reference_type&, const pointable_type&>
			cast_down(PP::overload_tag<type>) const noexcept override final
		{
			return {PP::placeholder, *this};
		}
	};
}
