#pragma once
#include <type_traits>

template <typename T>
constexpr inline bool is_user_defined_type = std::is_class_v<T> || std::is_union_v<T> || std::is_enum_v<T>;
