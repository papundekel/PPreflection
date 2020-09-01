#pragma once
#include "type_t.h"

template <typename Class, bool Explicit, typename... Args>
struct constructor_info {};

template <bool Explicit, typename... Args>
struct constructor_partial_info {};

template <typename Class>
struct make_full_info
{
	template <typename T>
	struct make	{};
	template <bool Explicit, typename... Args>
	struct make<constructor_partial_info<Explicit, Args...>> : type_t<constructor_info<Class, Explicit, Args...>> {};
};
