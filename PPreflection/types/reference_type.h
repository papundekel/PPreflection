#pragma once
#include "type.h"
#include "non_user_defined_type.h"

namespace PPreflection
{
	class referencable_type;

	class reference_type : public detail::non_user_defined_type<type>
	{
	public:
		constexpr virtual const referencable_type& remove_reference() const noexcept = 0;

		constexpr virtual bool is_lvalue() const noexcept = 0;

		template <bool rvalue>
		constexpr auto make_reference() const noexcept;
		constexpr auto make_reference(bool lvalue) const noexcept;
		constexpr auto make_reference() const noexcept;

		constexpr type_disjunction_reference<reference_type, pointable_type> reference_or_pointable() const noexcept override final
		{
			return *this;
		}

		constexpr bool can_be_initialized(const reference_type& initializer) const noexcept
		{
			return true;
		}

		constexpr bool has_name(std::string_view name) const noexcept override final
		{
			return false;
		}
		constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final;
		constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final;
	};
}
