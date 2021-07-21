#pragma once
#include "named_type.h"
#include "non_user_defined_type.h"
#include "pointable_type.h"

namespace PPreflection
{
	///
	/// @brief Represents the type @p void.
	///
	class void_type
		: public detail::non_user_defined_type<
			  detail::named_type<pointable_type>>
	{
	public:
		///
		/// @see named_descriptor::get_name()
		///
		constexpr PP::string_view get_name() const noexcept override final
		{
			return "void";
		}

		///
		/// @brief Compares two void types. Always returns true.
		///
		/// @return trues.
		///
		constexpr bool operator==(const void_type&) const noexcept
		{
			return true;
		}

		///
		/// @see type::operator==()
		///
		constexpr bool operator==(
			const type& other) const noexcept override final
		{
			return compare(*this, other);
		}

	private:
		constexpr PP::variant<const void_type&, const referencable_type&>
			cast_down(
				PP::overload_tag<pointable_type>) const noexcept override final
		{
			return {PP::placeholder, *this};
		}
	};

	namespace detail
	{
		template <typename>
		class basic_void_type final : public void_type
		{};
	}
}
