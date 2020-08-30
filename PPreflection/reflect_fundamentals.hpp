#pragma once
#include "reflect.hpp"

template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<void						>> = "void";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<decltype(nullptr)		>> = "std::nullptr_t";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<float					>> = "float";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<double					>> = "double";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<long double				>> = "long double";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<bool						>> = "bool";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<char						>> = "char";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<signed char				>> = "signed char";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<unsigned char			>> = "unsigned char";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<wchar_t					>> = "wchar_t";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<short int				>> = "short int";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<int						>> = "int";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<long int					>> = "long int";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<long long int			>> = "long long int";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<unsigned short int		>> = "unsigned short int";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<unsigned int				>> = "unsigned int";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<unsigned long int		>> = "unsigned long int";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<unsigned long long int	>> = "unsigned long long int";
#ifdef __cpp_char8_t
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<char8_t					>> = "char8_t";
#endif
#ifdef __cpp_unicode_characters
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<char16_t				>> = "char16_t";
template <> constexpr inline std::string_view detail::reflect_owning<detail::name_wrap<char32_t				>> = "char32_t";
#endif



template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<void							>> = 0;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<decltype(nullptr)				>> = 1;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<float							>> = 2;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<double							>> = 3;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<long double						>> = 4;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<bool							>> = 5;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<char							>> = 6;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<signed char						>> = 7;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<unsigned char					>> = 8;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<wchar_t							>> = 9;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<short int						>> = 10;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<int								>> = 11;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<long int						>> = 12;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<long long int					>> = 13;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<unsigned short int				>> = 14;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<unsigned int					>> = 15;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<unsigned long int				>> = 16;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<unsigned long long int			>> = 17;
#ifdef __cpp_char8_t
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<char8_t							>> = 18;
#endif
#ifdef __cpp_unicode_characters
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<char16_t						>> = 19;
template <> constexpr inline std::size_t detail::reflect_owning<detail::id_wrap<char32_t						>> = 20;
#endif
