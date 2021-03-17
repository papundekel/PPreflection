#pragma once
#include <string_view>

namespace PPreflector
{
	constexpr inline std::string_view tags_namespace_name = "PPreflection::tags::";
	constexpr inline std::string_view metadata_prefix = "template <> constexpr inline auto PPreflection::detail::metadata<";
}
