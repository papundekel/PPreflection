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

	template <> constexpr inline auto detail::metadata<tags::name<Namespace::global		>> = PP::string_view("");

	template <> constexpr inline auto detail::metadata<tags::name<void					>> = PP::string_view("void");
	template <> constexpr inline auto detail::metadata<tags::name<decltype(nullptr)		>> = PP::string_view("decltype(nullptr)");
	template <> constexpr inline auto detail::metadata<tags::name<float					>> = PP::string_view("float");
	template <> constexpr inline auto detail::metadata<tags::name<double				>> = PP::string_view("double");
	template <> constexpr inline auto detail::metadata<tags::name<long double			>> = PP::string_view("long double");
	template <> constexpr inline auto detail::metadata<tags::name<bool					>> = PP::string_view("bool");
	template <> constexpr inline auto detail::metadata<tags::name<char					>> = PP::string_view("char");
	template <> constexpr inline auto detail::metadata<tags::name<signed char			>> = PP::string_view("signed char");
	template <> constexpr inline auto detail::metadata<tags::name<unsigned char			>> = PP::string_view("unsigned char");
	template <> constexpr inline auto detail::metadata<tags::name<wchar_t				>> = PP::string_view("wchar_t");
	template <> constexpr inline auto detail::metadata<tags::name<short int				>> = PP::string_view("short int");
	template <> constexpr inline auto detail::metadata<tags::name<int					>> = PP::string_view("int");
	template <> constexpr inline auto detail::metadata<tags::name<long int				>> = PP::string_view("long int");
	template <> constexpr inline auto detail::metadata<tags::name<long long int			>> = PP::string_view("long long int");
	template <> constexpr inline auto detail::metadata<tags::name<unsigned short int	>> = PP::string_view("unsigned short int");
	template <> constexpr inline auto detail::metadata<tags::name<unsigned int			>> = PP::string_view("unsigned int");
	template <> constexpr inline auto detail::metadata<tags::name<unsigned long int		>> = PP::string_view("unsigned long int");
	template <> constexpr inline auto detail::metadata<tags::name<unsigned long long int>> = PP::string_view("unsigned long long int");
#ifdef __cpp_char8_t
	template <> constexpr inline auto detail::metadata<tags::name<char8_t				>> = PP::string_view("char8_t");
#endif
#ifdef __cpp_unicode_characters
	template <> constexpr inline auto detail::metadata<tags::name<char16_t				>> = PP::string_view("char16_t");
	template <> constexpr inline auto detail::metadata<tags::name<char32_t				>> = PP::string_view("char32_t");
#endif

	template <typename Class, typename... Parameters> constexpr inline auto detail::metadata<tags::is_explicit<Class, Parameters...>> = false;
	template <typename Class, typename... Parameters> constexpr inline auto detail::metadata<tags::constructor<Class, Parameters...>>
		= detail::basic_constructor<Class, Parameters...>{};
}
