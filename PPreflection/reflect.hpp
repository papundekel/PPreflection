#pragma once
#include <type_traits>
#include "reflect.h"
#include "value_t.h"
#include "map_pack.h"
#include "get_value.h"
#include "cref_t.h"
#include "../PP/PP/transform_view.hpp"
#include "../PP/PP/id.hpp"

namespace detail
{
	struct reflect__unspecialized_error {};

	template <typename T>
	constexpr inline reflect__unspecialized_error reflect_metadata = {};

	template <typename Overload, std::size_t Index>
	constexpr inline auto overload_caster = nullptr;
}

template <typename ResultType>
template <typename T>
constexpr const ResultType& detail::reflector<ResultType>::reflect<T>::value_f() noexcept
{
	if constexpr (!std::is_const_v<T> && !std::is_volatile_v<T> && (std::is_class_v<T> || std::is_enum_v<T>))
		return detail::reflect_metadata<T>;
	else
		return detail::reflect_metadata<detail::basic_type_wrap<T>>;
}

template <typename ResultType>
template <typename T>
constexpr const ResultType& detail::reflector<ResultType>::reflect<detail::id_wrap<T>>::value_f() noexcept
{
	return detail::reflect_metadata<detail::id_wrap<T>>;
}
template <typename ResultType>
template <typename T>
constexpr const ResultType& detail::reflector<ResultType>::reflect<detail::name_wrap<T>>::value_f() noexcept
{
	return detail::reflect_metadata<detail::name_wrap<T>>;
}
template <typename ResultType>
template <typename T>
constexpr const ResultType& detail::reflector<ResultType>::reflect<detail::constructor_wrap<T>>::value_f() noexcept
{
	return detail::reflect_metadata<detail::constructor_wrap<T>>;
}
template <typename ResultType>
template <typename T>
constexpr const ResultType& detail::reflector<ResultType>::reflect<detail::name_wrap<detail::constructor_wrap<T>>>::value_f() noexcept
{
	return detail::reflect_metadata<detail::name_wrap<T>>;
}

template <typename T, typename ResultType>
constexpr const ResultType& reflect() noexcept
{
	return get_value<typename detail::reflector<ResultType>::template reflect<T>>();
}

template <auto v, typename ResultType>
constexpr decltype(auto) reflect() noexcept
{
	return reflect<value_t<v>, ResultType>();
}

template <typename Pack, typename ResultType>
constexpr pointer_view<const cref_t<ResultType>> reflect_many() noexcept
{
	return get_value<map_pack<detail::reflector<ResultType>::template reflect, Pack, cref_t<ResultType>>>();
}

template <typename Pack, typename ResultType>
constexpr PP::view auto reflect_many_view() noexcept
{
	return reflect_many<Pack, ResultType>() | PP::transform(PP::id<const ResultType&>);
}

#include "basic_type.h"
#include "basic_class_constructor.h"

template <typename T> constexpr inline auto detail::reflect_metadata<detail::basic_type_wrap<T>> = detail::basic_type<T>{};
template <> constexpr inline auto detail::reflect_metadata<detail::name_wrap<detail::empty_id>> = std::string_view();

template <typename Class, bool Explicit, typename... Args>
constexpr inline auto detail::reflect_metadata<constructor_info<Class, Explicit, Args...>>
= detail::basic_class_constructor<Class, Explicit, type_pack<Args...>>{};

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
