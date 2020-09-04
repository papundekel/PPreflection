#pragma once
#include <type_traits>
#include "reflect.h"
#include "value_t.h"
#include "map_pack.h"
#include "get_value.h"
#include "cref_t.h"
#include "../PP/PP/transform_view.hpp"
#include "../PP/PP/id.hpp"
#include "basic_type.h"
#include "basic_class_constructor.h"
#include "basic_fundamental_type.h"
#include "basic_overloaded_fundamental_constructor.h"
#include "type_t.h"

namespace detail
{
	template <typename Overload, std::size_t Index>
	constexpr inline auto overload_caster = nullptr;

	struct reflect__unspecialized_error {};

	template <typename T>
	constexpr inline reflect__unspecialized_error reflect_metadata = {};

	constexpr inline const type& reflect_metadata_void = detail::basic_type<void>{};

	template <typename T>
	constexpr inline const type& reflect_metadata_fundamental_nonvoid = detail::basic_fundamental_type<T>{};

	template <typename T>
	constexpr inline const type& reflect_metadata_odd_type = detail::basic_type<T>{};

	template <typename T>
	constexpr inline const overloaded_constructor& reflect_metadata_fundamental_constructor
		= detail::basic_overloaded_fundamental_constructor<T>{};

	struct is_and_get_template__error {};

	template <template <typename> typename, typename>
	struct is_and_get_template : value_t<false>, type_t<is_and_get_template__error> {};
	template <template <typename> typename Template, typename T>
	struct is_and_get_template<Template, Template<T>> : value_t<true>, type_t<T> {};
}

template <typename ResultType>
template <typename T>
constexpr const ResultType& detail::reflector<ResultType>::reflect<T>::value_f() noexcept
{
	using NW = detail::is_and_get_template<detail::name_wrap, T>;
	using CW = detail::is_and_get_template<detail::constructor_wrap, T>;
	using IW = detail::is_and_get_template<detail::id_wrap, T>;

	if constexpr (get_value<CW>())
	{
		using CT = get_type<CW>;
		if constexpr (std::is_fundamental_v<CT>)
			return detail::reflect_metadata_fundamental_constructor<CT>;
		else
			return detail::reflect_metadata<T>;
	}
	else if constexpr (get_value<NW>() || get_value<IW>())
		return detail::reflect_metadata<T>;
	else
	{
		if constexpr (!std::is_const_v<T> && !std::is_volatile_v<T>)
		{
			if constexpr (std::is_class_v<T> || std::is_enum_v<T>)
				return detail::reflect_metadata<T>;
			else if constexpr (std::is_void_v<T>)
				return detail::reflect_metadata_void;
			else if constexpr (std::is_fundamental_v<T>)
				return detail::reflect_metadata_fundamental_nonvoid<T>;
			else
				return detail::reflect_metadata_odd_type<T>;
		}
		else
			return detail::reflect_metadata_odd_type<T>;
	}
}

template <typename T, typename ResultType>
constexpr const ResultType& reflect() noexcept
{
	return get_value<typename detail::reflector<ResultType>::template reflect<T>>();
}

template <auto v, typename ResultType>
constexpr const ResultType& reflect() noexcept
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
