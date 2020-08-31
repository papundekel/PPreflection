#pragma once
#include "type_t.h"

template <typename Class, typename... Args>
struct constructor_info {};

template <typename Class>
struct make_full_info
{
	template <typename T>
	struct make	{};
	template <typename... Args>
	struct make<type_pack<Args...>> : type_t<constructor_info<Class, Args...>> {};
};
