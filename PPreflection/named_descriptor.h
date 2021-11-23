#pragma once
#include "PP/concepts/derived_from.hpp"
#include "PP/view_equal.hpp"

#include "descriptor.h"

namespace PPreflection
{
///
/// @brief Represents an entity with a non-compound name.
///
template <typename Base>
class named_descriptor : public Base
{
	static_assert(PP::concepts::derived_from<Base, descriptor>);

public:
	///
	/// @brief Gets the name of the entity.
	///
	constexpr virtual PP::string_view get_name() const noexcept = 0;

	///
	/// @see @ref descriptor::has_name().
	///
	constexpr bool has_name(PP::string_view name) const noexcept override final
	{
		return PP::view_equal(get_name(), name);
	}
};
}
