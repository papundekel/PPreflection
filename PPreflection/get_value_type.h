#pragma once
#include "get_type.h"
#include "get_value.h"

template <typename T>
using get_value_type = decltype(get_value<T>());
