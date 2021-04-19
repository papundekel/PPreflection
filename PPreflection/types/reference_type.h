#pragma once
#include "non_user_defined_type.h"
#include "type.h"

namespace PPreflection
{
	template <typename>
	class cv_type;

	class referencable_type;

	class reference_type : public detail::non_user_defined_type<type>
	{
	public:
		constexpr PP::variant<const reference_type&, const pointable_type&> cast_down(PP::overload_tag<type>) const noexcept override final
		{
			return {PP::placeholder, *this};
		}
		
		constexpr virtual cv_type<referencable_type> remove_reference() const noexcept = 0;

		constexpr virtual bool is_lvalue() const noexcept = 0;

		constexpr auto make_reference(bool lvalue) const noexcept;
		constexpr auto make_reference() const noexcept;

		constexpr bool has_name(PP::string_view) const noexcept override final
		{
			return false;
		}
		constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final;
		constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final;

		constexpr bool operator==(const reference_type& other) const noexcept;
		constexpr bool operator==(const type& other) const noexcept override final
		{
			return compare(*this, other);
		}
	};
}
