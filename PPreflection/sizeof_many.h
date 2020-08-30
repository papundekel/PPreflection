#pragma once
#include "value_t.h"

template <typename... T>
struct sizeof_many : value_t<sizeof...(T)> {};
