#pragma once
#include "type_t.h"

template <typename Class, typename Args, bool Noexcept>
struct constructor_info {};

template <typename Args, bool Noexcept>
struct constructor_partial_info {};

template <typename Class>
struct make_full_info
{
	template <typename T>
	struct make	{};
	template <typename Args, bool Noexcept>
	struct make<constructor_partial_info<Args, Noexcept>> : type_t<constructor_info<Class, Args, Noexcept>>	{};
};
