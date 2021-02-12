#pragma once
#include "apply_template.hpp"
#include "dynamic_object.hpp"
#include "dynamic_reference.hpp"
#include "functional/id.hpp"
#include "fundamental_type_pack.h"
#include "get_type_class.hpp"
#include "reflect.h"
#include "template_tuple.hpp"
#include "transform_view.hpp"
#include "tuple_map.hpp"
#include "type_t.hpp"
#include "value_t.hpp"

#include "types/types.hpp"
#include "types/implementations/implementations.hpp"

#include "basic_namespace.h"

#include "functions/functions.h"
#include "functions/implementations/implementations.h"

#include "descriptor.hpp"

#include "functions/function.hpp"
#include "functions/member_function.hpp"

#include "types/dynamic_function_type.h"
#include "make_array.h"
#include "types/dynamic_enum_type.h"

namespace PPreflection
{
	namespace detail
	{
		struct overload_caster__no_specialization {};

		template <typename Overload, std::size_t Index>
		constexpr inline overload_caster__no_specialization overload_caster = {};

		constexpr inline auto basic_types = PP::template_tuple<
			basic_reference_type,
			basic_void_type,
			basic_function_type,
			basic_unknown_bound_array_type,
			basic_known_bound_array_type,
			basic_non_void_fundamental_type,
			basic_pointer_type,
			basic_pointer_to_member_type,
			basic_non_union_class_type,
			basic_union_type,
			basic_enum_type>;

		template <typename T>
		constexpr inline auto metadata = detail::basic_types[PP::value_t_static_cast(PP::type_size_t, get_type_class_value_t(PP::type<T>))](PP::type<T>)();

		template <typename T>
		constexpr auto&& reflect_helper(PP::type_t<T>) noexcept
		{
			return metadata<T>;
		}
	}

	using namespace std::literals::string_view_literals;

	template <> constexpr inline auto detail::metadata<tags::name<Namespace::global		>> = ""sv;

	template <> constexpr inline auto detail::metadata<tags::name<void					>> = "void"sv;
	template <> constexpr inline auto detail::metadata<tags::name<decltype(nullptr)		>> = "decltype(nullptr)"sv;
	template <> constexpr inline auto detail::metadata<tags::name<float					>> = "float"sv;
	template <> constexpr inline auto detail::metadata<tags::name<double				>> = "double"sv;
	template <> constexpr inline auto detail::metadata<tags::name<long double			>> = "long double"sv;
	template <> constexpr inline auto detail::metadata<tags::name<bool					>> = "bool"sv;
	template <> constexpr inline auto detail::metadata<tags::name<char					>> = "char"sv;
	template <> constexpr inline auto detail::metadata<tags::name<signed char			>> = "signed char"sv;
	template <> constexpr inline auto detail::metadata<tags::name<unsigned char			>> = "unsigned char"sv;
	template <> constexpr inline auto detail::metadata<tags::name<wchar_t				>> = "wchar_t"sv;
	template <> constexpr inline auto detail::metadata<tags::name<short int				>> = "short int"sv;
	template <> constexpr inline auto detail::metadata<tags::name<int					>> = "int"sv;
	template <> constexpr inline auto detail::metadata<tags::name<long int				>> = "long int"sv;
	template <> constexpr inline auto detail::metadata<tags::name<long long int			>> = "long long int"sv;
	template <> constexpr inline auto detail::metadata<tags::name<unsigned short int	>> = "unsigned short int"sv;
	template <> constexpr inline auto detail::metadata<tags::name<unsigned int			>> = "unsigned int"sv;
	template <> constexpr inline auto detail::metadata<tags::name<unsigned long int		>> = "unsigned long int"sv;
	template <> constexpr inline auto detail::metadata<tags::name<unsigned long long int>> = "unsigned long long int"sv;
#ifdef __cpp_char8_t
	template <> constexpr inline auto detail::metadata<tags::name<char8_t				>> = "char8_t"sv;
#endif
#ifdef __cpp_unicode_characters
	template <> constexpr inline auto detail::metadata<tags::name<char16_t				>> = "char16_t"sv;
	template <> constexpr inline auto detail::metadata<tags::name<char32_t				>> = "char32_t"sv;
#endif

	template <typename Class, typename... Parameters> constexpr inline auto detail::metadata<tags::is_explicit<Class, Parameters...>> = false;
	template <typename Class, typename... Parameters> constexpr inline auto detail::metadata<tags::constructor<Class, Parameters...>>
		= detail::basic_constructor<Class, Parameters...>{};
}
