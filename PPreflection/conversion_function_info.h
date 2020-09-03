#pragma once
#include "cv_qualifier.h"
#include "ref_qualifier.h"
#include "type_t.h"
#include "overload_cast.h"

template <typename C, typename R>
struct overloaded_conversion_function_info
{
	using Class = C;
	using Result = R;
};

template <bool Explicit, cv_qualifier cv, ref_qualifier ref>
struct conversion_function_info {};

template <typename Class, typename Result>
struct make_conversion_function
{
	template <typename T>
	struct make {};
	template <bool Explicit, cv_qualifier cv, ref_qualifier ref>
	struct make<conversion_function_info<Explicit, cv, ref>>
		: type_t<value_t<overload_member_caster<cv, ref>(&Class::operator Result)>> {};
};
