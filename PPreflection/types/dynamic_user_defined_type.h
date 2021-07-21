#pragma once
#include "../class_or_namespace.h"
#include "dynamic_named_descriptor.h"
#include "user_defined_type.h"

namespace PPreflection::detail
{
template <typename Base>
class dynamic_user_defined_type : public dynamic_named_descriptor<Base>
{
	static_assert(PP::concepts::derived_from<Base, user_defined_type>);

	class_or_namespace parent;

public:
	constexpr dynamic_user_defined_type(PP::string_view name,
	                                    class_or_namespace parent) noexcept
		: dynamic_named_descriptor<Base>(name)
		, parent(parent)
	{}

	constexpr class_or_namespace get_parent(int) const noexcept override final
	{
		return parent;
	}
};
}
