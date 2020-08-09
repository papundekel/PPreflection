#pragma once
#include <type_traits>
#include "type_pack.hpp"

namespace detail
{
	template <typename T>
	struct get_function_t;
	template <typename Return, typename... Parameters>
	struct get_function_t<Return(Parameters...)>
	{
		using return_t = Return;
		using parameters_t = type_pack<Parameters...>;
	};
}
template <template <typename> typename T, auto x>
using decltype_t = T<decltype(x)>;

template <template <typename> typename F, template <typename> typename G>
struct compound
{
	template <typename T>
	using type = F<G<T>>;
};

template <typename T>
using return_type_t = detail::get_function_t<T>::return_t;
template <auto f>
using return_type_t_f = decltype_t<compound<return_type_t, std::remove_pointer_t>::type, f>;

template <typename T>
using parameter_types_t = detail::get_function_t<T>::parameters_t;
template <auto f>
using parameter_types_t_f = decltype_t<compound<parameter_types_t, std::remove_pointer_t>::type, f>;
