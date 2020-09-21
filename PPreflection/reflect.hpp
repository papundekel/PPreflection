#pragma once
#include <type_traits>
#include "reflect.h"
#include "transform_view.hpp"
#include "functional/id.hpp"
#include "is_user_defined_type.h"
#include "value_t.hpp"
#include "type_t.hpp"
#include "fundamental_type_pack.h"
#include "types/types.h"

namespace detail
{
	template <typename Overload, std::size_t Index>
	constexpr inline auto overload_caster = nullptr;

	struct reflect__unspecialized_error {};

	template <typename T>
	constexpr inline reflect__unspecialized_error reflect_metadata = {};

	template <typename T>
	constexpr inline auto reflect_metadata_implicit = basic_implementation<T>{};

	struct is_and_get_template__error {};

	template <template <typename...> typename, typename>
	struct is_and_get_template : PP::value_t<false>, PP::type_t<is_and_get_template__error> {};
	template <template <typename...> typename Template, typename T, typename... U>
	struct is_and_get_template<Template, Template<T, U...>> : PP::value_t<true>, PP::type_t<T> {};
}

template <typename ResultType>
template <typename T>
constexpr ResultType detail::reflector<ResultType>::reflect<T>::value_f() noexcept
{
	using NW = detail::is_and_get_template<detail::name_wrap, T>;
	using IW = detail::is_and_get_template<detail::id_wrap, T>;
	using OCI = detail::is_and_get_template<overloaded_constructor_info, T>;
	using CI = detail::is_and_get_template<constructor_info, T>;

	return detail::reflect_metadata_generated<T>;
}

template <typename T, typename ResultType>
constexpr ResultType reflect() noexcept
{
	return PP::get_value<typename detail::reflector<ResultType>::template reflect<T>>();
}

template <auto v, typename ResultType>
constexpr ResultType reflect() noexcept
{
	return reflect<PP::value_t<v>, ResultType>();
}

template <typename Pack, typename ResultType>
constexpr PP::view auto reflect_many() noexcept
{
	if constexpr (std::is_reference_v<ResultType>)
		return PP::get_value<PP::map_pack<detail::reflector<ResultType>::template reflect, Pack, PP::reference_wrapper<ResultType>>>()
			| PP::transform(PP::id<ResultType>);
	else
		return PP::get_value<PP::map_pack<detail::reflector<ResultType>::template reflect, Pack, ResultType>>();
}

template <typename Class, typename... Args>
constexpr inline auto detail::reflect_metadata<constructor_info<Class, Args...>>
	= detail::basic_class_constructor<Class, reflect<detail::is_explicit_constructor<Class, Args...>, bool>(), PP::type_pack<Args...>>{};

template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<void					>> = "void";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<decltype(nullptr)		>> = "std::nullptr_t";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<float					>> = "float";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<double					>> = "double";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<long double			>> = "long double";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<bool					>> = "bool";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<char					>> = "char";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<signed char			>> = "signed char";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<unsigned char			>> = "unsigned char";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<wchar_t				>> = "wchar_t";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<short int				>> = "short int";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<int					>> = "int";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<long int				>> = "long int";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<long long int			>> = "long long int";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<unsigned short int		>> = "unsigned short int";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<unsigned int			>> = "unsigned int";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<unsigned long int		>> = "unsigned long int";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<unsigned long long int	>> = "unsigned long long int";
#ifdef __cpp_char8_t
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<char8_t				>> = "char8_t";
#endif
#ifdef __cpp_unicode_characters
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<char16_t				>> = "char16_t";
template <> constexpr inline std::string_view detail::reflect_metadata<detail::name_wrap<char32_t				>> = "char32_t";
#endif
