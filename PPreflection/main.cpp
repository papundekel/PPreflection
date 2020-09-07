#include <iostream>
#include <variant>

#include "get_value.hpp"

#include "value_pack.h"
#include "apply_pack.h"
#include "map_pack.h"
#include "append_pack.h"
#include "overload_cast.h"

#include "to_chars.hpp"

#include "simple_ostream.hpp"
#include "basic_ostream.hpp"

#include "cref_t.hpp"

#include "dynamic_reference.hpp"
#include "dynamic_object.hpp"

#include "descriptor.hpp"
#include "function.hpp"
#include "type.hpp"
#include "maybe_static_member_function.hpp"
#include "member_function.hpp"
#include "namespace_function.hpp"
#include "namespace_t.hpp"
#include "conversion_function.h"
#include "constructor.h"

#include "overloaded_function.hpp"
#include "overloaded_member_function.hpp"
#include "overloaded_conversion_function.hpp"
#include "overloaded_namespace_function.h"
#include "descriptor.hpp"

#include "basic_namespace.h"
#include "basic_function.h"
#include "basic_class_constructor.h"
#include "basic_class_type.h"
#include "basic_type.hpp"
#include "basic_fundamental_type.h"
#include "basic_typed_function.h"
#include "basic_static_function.h"
#include "basic_member_function.h"
#include "basic_namespace_function.h"
#include "basic_conversion_function.h"

#include "basic_overloaded_class_constructor.h"
#include "basic_overloaded_conversion_function.h"
#include "basic_overloaded_function.h"
#include "basic_overloaded_member_function.h"
#include "basic_overloaded_namespace_function.h"
#include "basic_overloaded_static_member_function.h"

#include "prepend_pack.h"
#include "filter_pack.h"

#include "fundamental_type_pack.h"

#include "constructor_info.h"
#include "conversion_function_info.h"

struct X
{
	int x;

	X(const int& x)
		: x(x)
	{
		std::cout << "int ctr " << x << "\n";
	}

	explicit X(const double& y)
		: x(y)
	{
		std::cout << "double ctr\n";
	}

	X(int a, int b)
		: x(a * b)
	{
		std::cout << "X::X(int, int)\n";
	}

	void f() &
	{
		std::cout << x << "f&\n";
	}
	void f() &&
	{
		std::cout << x << "f&&\n";
	}

	explicit operator int()
	{
		std::cout << "operator int\n";
		return 1;
	}
	operator int() const
	{
		std::cout << "operator int const\n";
		return 0;
	}

	~X()
	{
		std::cout << "dead, " << x << '\n';
	}
};

X double_(const int& x) noexcept
{
	return X(2 * x);
}
X double_(const double& x)
{
	return X(2 * x);
}

#include "reflect.hpp"

namespace reflect_detail
{
	struct X_f {};
	struct global_double_ {};
}

template <> constexpr inline auto detail::reflect_metadata<detail::name_wrap<namespace_t::global>> = std::string_view("global'");
template <> constexpr inline auto detail::reflect_metadata<namespace_t::global> =
detail::basic_namespace<namespace_t::global, append_pack<fundamental_type_pack,
	type_pack<X>>,
	type_pack<reflect_detail::global_double_>>{};

template <> constexpr inline auto detail::reflect_metadata<detail::name_wrap<X>> = std::string_view("X");
template <> constexpr inline auto detail::reflect_metadata<detail::id_wrap<X>> = std::size_t(0);
template <> constexpr inline auto detail::reflect_metadata<X> = detail::basic_class_type<namespace_t::global, X,
	type_pack<
	reflect_detail::X_f,
	overloaded_conversion_function_info<X, int>>,
	type_pack<>>{};

template <> constexpr inline auto detail::reflect_metadata<detail::constructor_wrap<X>>
	= detail::basic_overloaded_class_constructor<X, type_pack<
		constructor_partial_info<false, const int&>,
		constructor_partial_info<true, const double&>>>{};

namespace detail
{
	template <>	constexpr inline auto overload_caster<reflect_detail::X_f, 0> = overload_member_caster<cv_qualifier::none, ref_qualifier::lvalue>(&X::f);
	template <>	constexpr inline auto overload_caster<reflect_detail::X_f, 1> = overload_member_caster<cv_qualifier::none, ref_qualifier::rvalue>(&X::f);
}

template <> constexpr inline auto detail::reflect_metadata<detail::name_wrap<reflect_detail::X_f>> = std::string_view("f");
template <> constexpr inline auto detail::reflect_metadata<reflect_detail::X_f>
	= detail::basic_overloaded_member_function<reflect_detail::X_f, value_pack<
		detail::overload_caster<reflect_detail::X_f, 0>,
		detail::overload_caster<reflect_detail::X_f, 1>>>{};

template <> constexpr inline auto detail::reflect_metadata<value_t<detail::overload_caster<reflect_detail::X_f, 0>>>
	= detail::basic_member_function<reflect_detail::X_f, detail::overload_caster<reflect_detail::X_f, 0>>{};
template <> constexpr inline auto detail::reflect_metadata<value_t<detail::overload_caster<reflect_detail::X_f, 1>>>
	= detail::basic_member_function<reflect_detail::X_f, detail::overload_caster<reflect_detail::X_f, 1>>{};

template <> constexpr inline auto detail::reflect_metadata<detail::name_wrap<reflect_detail::global_double_>> = std::string_view("double_");
template <> constexpr inline auto detail::reflect_metadata<reflect_detail::global_double_>
	= detail::basic_overloaded_namespace_function<reflect_detail::global_double_, namespace_t::global, value_pack<
		::overload_caster<const int&>(double_),
		::overload_caster<const double&>(double_)>>{};

template <> constexpr inline auto detail::reflect_metadata<value_t<::overload_caster<const int&>(double_)>>
	= detail::basic_namespace_function<reflect_detail::global_double_, ::overload_caster<const int&>(double_)>{};
template <> constexpr inline auto detail::reflect_metadata<value_t<::overload_caster<const double&>(double_)>>
	= detail::basic_namespace_function<reflect_detail::global_double_, ::overload_caster<const double&>(double_)>{};

template <> constexpr inline auto detail::reflect_metadata<overloaded_conversion_function_info<X, int>>
	= detail::basic_overloaded_conversion_function<overloaded_conversion_function_info<X, int>, type_pack<
		conversion_function_info<true, cv_qualifier::none, ref_qualifier::none>,
		conversion_function_info<false, cv_qualifier::const_, ref_qualifier::none>>>{};

namespace detail
{
	template <>	constexpr inline auto overload_caster<overloaded_conversion_function_info<X, int>, 0>
		= overload_member_caster<cv_qualifier::none, ref_qualifier::none>(&X::operator int);
	template <>	constexpr inline auto overload_caster<overloaded_conversion_function_info<X, int>, 1>
		= overload_member_caster<cv_qualifier::const_, ref_qualifier::none>(&X::operator int);
}

template <> constexpr inline auto detail::reflect_metadata<value_t<detail::overload_caster<overloaded_conversion_function_info<X, int>, 0>>>
	= detail::basic_conversion_function<detail::overload_caster<overloaded_conversion_function_info<X, int>, 0>, false>{};
template <> constexpr inline auto detail::reflect_metadata<value_t<detail::overload_caster<overloaded_conversion_function_info<X, int>, 1>>>
	= detail::basic_conversion_function<detail::overload_caster<overloaded_conversion_function_info<X, int>, 1>, false>{};

int main()
{
	auto double_f = reflect<namespace_t::global, namespace_t>().get_function("double_");
	if (double_f)
	{
		auto x = double_f->invoke({ 5 });
	}

	std::cout.flush();
	return 0;
}
