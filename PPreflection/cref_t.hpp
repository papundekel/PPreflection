#pragma once
#include <functional>

template <typename T>
using cref_t = std::reference_wrapper<const T>;
