#pragma once
#include <typeindex>

namespace PPreflection
{
	class non_union_class_type;

	[[maybe_unused]] static const non_union_class_type& reflect_polymorphic(
		std::type_index type);
}
