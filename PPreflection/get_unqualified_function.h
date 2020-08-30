#pragma once
#include "apply_pack.h"
#include "get_function_info.h"

template <typename ReturnType>
struct make_function_type
{
	template <typename... ParameterTypes>
	struct make : type_t<ReturnType(ParameterTypes...)>	{};
};

template <typename F>
struct get_unqualified_function : apply_pack<
		make_function_type<typename get_function_info<F>::return_type>::template make,
		typename get_function_info<F>::parameter_types> {};
