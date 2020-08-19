#include <iostream>

#include "value_pack.h"
#include "overload_cast.h"
#include "append_pack.h"
#include "map_pack.h"
#include "apply_pack.h"

#include "get_value.hpp"

#include "reflect.hpp"
#include "reflect_fundamentals.hpp"

#include "unique_ptr.hpp"
#include "simple_vector.hpp"
#include "to_chars.hpp"

#include "simple_ostream.hpp"
#include "array_ostream.hpp"
#include "string_ostream.hpp"

#include "cref_t.hpp"
#include "simple_range.hpp"
#include "dynamic_ptr.hpp"
#include "dynamic_wrap.hpp"
#include "descriptor.hpp"

#include "function.hpp"
#include "member_function.hpp"
#include "member_like_function.hpp"
#include "namespace_function.hpp"
#include "namespace_t.hpp"

#include "overloaded_function.hpp"
#include "overloaded_member_function.hpp"

#include "basic_namespace.hpp"
#include "basic_function.hpp"
#include "basic_class_constructor.hpp"
#include "basic_class_type.hpp"
#include "basic_type.hpp"
#include "basic_typed_function.hpp"
#include "basic_static_function.hpp"
#include "basic_member_function.hpp"
#include "basic_namespace_function.hpp"
#include "basic_static_member_function.hpp"

#include "basic_overloaded_constructor.hpp"
#include "basic_overloaded_function.hpp"
#include "basic_overloaded_namespace_function.hpp"
#include "basic_overloaded_member_function.hpp"
#include "basic_overloaded_static_member_function.hpp"

#include "prepend_pack.h"
#include "filter_pack.h"

#include "fundamental_type_pack.h"

struct X
{
	int x;

	X(int x)
		: x(x)
	{}

	void f(const int& y) &&
	{
		std::cout << x + y << "&&\n";
	}
	void f(const int& y) &
	{
		std::cout << x + y << "&\n";
	}
	void f(const int& y) const& noexcept
	{
		std::cout << x + y << "const& noexcept\n";
	}
};

int f(X& x) noexcept
{
	return x.x;
}

template <typename T> constexpr inline auto detail::reflect_owning<detail::basic_type_wrap<T>> = detail::basic_type<T>{};

template <> constexpr inline auto detail::reflect_owning<detail::name_wrap<namespace_t::global>> = std::string_view("global'");
template <> constexpr inline auto detail::reflect_owning<namespace_t::global> =
	detail::basic_namespace<namespace_t::global, fundamental_type_pack,	value_pack<>>{};

namespace overload
{
	template <typename Overload, std::size_t Index>
	constexpr inline auto caster = nullptr;
}

namespace overload
{
	struct X_f {};
	template <>	constexpr inline auto caster<X_f, 0> = overload_member_caster<cv_qualifier::none, ref_qualifier::rvalue, const int&>;
	template <>	constexpr inline auto caster<X_f, 1> = overload_member_caster<cv_qualifier::none, ref_qualifier::lvalue, const int&>;
	template <>	constexpr inline auto caster<X_f, 2> = overload_member_caster<cv_qualifier::const_, ref_qualifier::lvalue, const int&>;
}

template <> constexpr inline auto detail::reflect_owning<detail::name_wrap<X>> = std::string_view("X");
template <> constexpr inline auto detail::reflect_owning<detail::id_wrap<X>> = std::size_t(1);
template <> constexpr inline auto detail::reflect_owning<X> = detail::basic_class_type<namespace_t::global, X,
	type_pack<overload::X_f>,
	type_pack<>>{};

template <> constexpr inline auto detail::reflect_owning<detail::name_wrap<overload::X_f>> = std::string_view("f");
template <> constexpr inline auto detail::reflect_owning<overload::X_f>
	= detail::basic_overloaded_member_function<overload::X_f, value_pack<
		overload::caster<overload::X_f, 0>(&X::f),
		overload::caster<overload::X_f, 1>(&X::f),
		overload::caster<overload::X_f, 2>(&X::f)>>{};

template <> constexpr inline auto detail::reflect_owning<value_t<overload::caster<overload::X_f, 0>(&X::f)>>
	= detail::basic_member_function<overload::X_f, overload::caster<overload::X_f, 0>(&X::f)>{};

template <> constexpr inline auto detail::reflect_owning<value_t<overload::caster<overload::X_f, 1>(&X::f)>>
	= detail::basic_member_function<overload::X_f, overload::caster<overload::X_f, 1>(&X::f)>{};

template <> constexpr inline auto detail::reflect_owning<value_t<overload::caster<overload::X_f, 2>(&X::f)>>
	= detail::basic_member_function<overload::X_f, overload::caster<overload::X_f, 2>(&X::f)>{};

namespace overload { struct global_f {}; }
template <> constexpr inline auto detail::reflect_owning<detail::name_wrap<overload::global_f>> = std::string_view("f");
template <> constexpr inline auto detail::reflect_owning<overload::global_f>
	= detail::basic_overloaded_namespace_function<overload::global_f, namespace_t::global, value_pack<
		f>>{};

template <> constexpr inline auto detail::reflect_owning<value_t<f>> = detail::basic_namespace_function<overload::global_f, f>{};

int main()
{
	const type& x = reflect<X, type>();
	if (auto* f = x.get_member_function("f"); f)
	{
		const X x(78);
		f->invoke(x, { 8 });
	}

	std::cout.flush();
	return 0;
}
