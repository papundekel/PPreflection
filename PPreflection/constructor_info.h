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

template <typename Info>
struct is_one_p_conversion_info : value_t<false> {};
template <typename Class, bool Explicit, typename... Args>
struct is_one_p_conversion_info<constructor_info<Class, Explicit, Args...>> : value_t<!Explicit && sizeof...(Args) == 1> {};
