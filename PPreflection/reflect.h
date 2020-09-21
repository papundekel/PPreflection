#pragma once
#include "pointer_view.h"
#include "view.hpp"
#include "value_t.hpp"
#include "type_t.hpp"
#include "overload_cast.h"

template <typename Class>
struct overloaded_constructor_info {};

template <typename Class, typename... Args>
struct constructor_info {};

template <bool Explicit, typename... Args>
struct constructor_partial_info {};

template <typename Class>
struct make_full_info
{
	template <typename T>
	struct make {};
	template <typename... Args>
	struct make<PP::type_pack<Args...>> : PP::type_t<constructor_info<Class, Args...>> {};
};
template <typename T>
struct strip_partial_info {};
template <bool Explicit, typename... Args>
struct strip_partial_info<constructor_partial_info<Explicit, Args...>> : PP::type_t<PP::type_pack<Args...>> {};

template <typename Info>
struct is_one_p_conversion_info : PP::value_t<false> {};
template <bool Explicit, typename... Args>
struct is_one_p_conversion_info<constructor_partial_info<Explicit, Args...>> : PP::value_t<!Explicit && sizeof...(Args) == 1> {};

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

namespace detail
{
	template <typename T>
	struct name_wrap {};

	template <typename T>
	struct id_wrap {};

	template <typename T>
	struct base_classes {};

	template <typename Class, typename... Args>
	struct is_explicit_constructor {};

	template <typename T>
	struct member_functions {};

	template <typename T>
	struct static_member_functions {};

	template <typename T>
	struct nested_classes {};

	template <typename ResultType>
	struct reflector
	{
		template <typename T>
		struct reflect
		{
			static constexpr ResultType value_f() noexcept;
		};
	};
}

template <typename T, typename ResultType>
constexpr ResultType reflect() noexcept;

template <auto v, typename ResultType>
constexpr ResultType reflect() noexcept;

template <typename Pack, typename ResultType>
constexpr PP::view auto reflect_many() noexcept;
