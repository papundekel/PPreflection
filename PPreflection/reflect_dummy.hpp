#pragma once
#include "reflect.hpp"

#include "PP/empty_tuple.hpp"

template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::namespaces<PPreflection::Namespace::global>> = PP::empty_tuple{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::types	   <PPreflection::Namespace::global>> = PP::empty_tuple{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::functions <PPreflection::Namespace::global>> = PP::empty_tuple{};
