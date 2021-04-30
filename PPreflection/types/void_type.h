#pragma once
#include "named_type.h"
#include "non_user_defined_type.h"
#include "pointable_type.h"

namespace PPreflection
{
	class void_type
		: public detail::non_user_defined_type<
			  detail::named_type<pointable_type>>
	{
	public:
		constexpr PP::variant<const void_type&, const referencable_type&>
			cast_down(
				PP::overload_tag<pointable_type>) const noexcept override final
		{
			return { PP::placeholder, *this };
		}

		constexpr PP::string_view get_name() const noexcept override final
		{
			return "void";
		}
		constexpr bool operator==(const void_type&) const noexcept
		{
			return true;
		}
		constexpr bool operator==(
			const type& other) const noexcept override final
		{
			return compare(*this, other);
		}
	};

	template <typename>
	class basic_void_type : public void_type
	{};
}
