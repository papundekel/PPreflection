#pragma once
#include "../PP/PP/type_t.hpp"
#include "../PP/PP/value_t.hpp"
#include "overload_cast.h"

template <typename C, typename R>
struct overloaded_conversion_function_info
{
	using Class = C;
	using Result = R;
};

template <bool Explicit, PP::cv_qualifier cv, PP::ref_qualifier ref>
struct conversion_function_info {};

template <typename Class, typename Result>
struct make_conversion_function
{
	template <typename T>
	struct make {};
	template <bool Explicit, PP::cv_qualifier cv, PP::ref_qualifier ref>
	struct make<conversion_function_info<Explicit, cv, ref>>
		: PP::type_t<PP::value_t<overload_member_caster<cv, ref>(&Class::operator Result)>> {};
};
