#pragma once
#include "get_function_info.hpp"
#include "make_function_type.hpp"
#include "functional/compose.hpp"
#include "concepts::valueper.hpp"

constexpr inline auto get_unqualified_function =
	PP::make_function_type
	|
	concepts::valueper<compose<true, false>(
		[]<typename Return, typename... Parameters>(PP::function_info<Return, Parameters...>)
		{
			return PP::function_info(PP::type<Return(Parameters...)>);
		}, PP::get_function_info)>;
