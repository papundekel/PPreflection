#pragma once
#include "implementations/basic_non_array_object_type.hpp"
#include "non_void_fundamental_type.h"

namespace PPreflection
{
///
/// @brief Represent the type of @p nullptr.
///
///
class null_type
	: public detail::basic_non_array_object_type<decltype(nullptr),
                                                 non_void_fundamental_type>
{
public:
	constexpr PP::string_view get_name() const noexcept override final
	{
		return "decltype(nullptr)";
	}

	constexpr bool operator==(const null_type&) const noexcept
	{
		return true;
	}

	constexpr bool operator==(const type& other) const noexcept override final
	{
		return compare(*this, other);
	}

	dynamic_object create_instance() const noexcept override final;

	constexpr detail::standard_conversion_sequence
	make_standard_conversion_sequence_impl(
		const non_array_object_type& target) const noexcept override final;
};

namespace detail
{
template <typename>
class basic_null_type final : public null_type
{};
}
}
