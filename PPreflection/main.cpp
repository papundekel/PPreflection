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
#include "member_function.hpp"
#include "namespace_function.hpp"
#include "namespace_t.hpp"
#include "conversion_function.h"

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
#include "basic_typed_function.h"
#include "basic_static_function.h"
#include "basic_member_function.h"
#include "basic_namespace_function.h"
#include "basic_conversion_function.h"

#include "basic_overloaded_constructor.h"
#include "basic_overloaded_conversion_function.h"
#include "basic_overloaded_function.h"
#include "basic_overloaded_member_function.h"
#include "basic_overloaded_namespace_function.h"
#include "basic_overloaded_static_member_function.h"

#include "prepend_pack.h"
#include "filter_pack.h"

#include "fundamental_type_pack.h"

#include "constructor_info.h"

struct X
{
	int x;

	X(const int& x)
		: x(x)
	{
		std::cout << "int ctr\n";
	}

	explicit X(const double& y)
		: x(y)
	{
		std::cout << "double ctr\n";
	}

	void f() &
	{
		std::cout << x << "&\n";
	}
	void f() &&
	{
		std::cout << x << "&&\n";
	}

	operator int()
	{
		return 7;
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

namespace detail
{
	struct reflect__unspecialized_error {};

	template <typename T>
	constexpr inline reflect__unspecialized_error reflect_owning = {};
}

#include "reflect.hpp"
#include "reflect_fundamentals.hpp"

template <typename T> constexpr inline auto detail::reflect_owning<detail::basic_type_wrap<T>> = detail::basic_type<T>{};

template <typename Class, bool Explicit, typename... Args>
constexpr inline auto detail::reflect_owning<constructor_info<Class, Explicit, Args...>>
	= detail::basic_class_constructor<Class, Explicit, type_pack<Args...>>{};

namespace overload { struct global_double_ {}; }
template <> constexpr inline auto detail::reflect_owning<detail::name_wrap<overload::global_double_>> = std::string_view("double_");
template <> constexpr inline auto detail::reflect_owning<overload::global_double_>
	= detail::basic_overloaded_namespace_function<overload::global_double_, namespace_t::global, value_pack<
		double_>>{};

template <> constexpr inline auto detail::reflect_owning<value_t<double_>> = detail::basic_namespace_function<overload::global_double_, double_>{};

template <> constexpr inline auto detail::reflect_owning<detail::name_wrap<namespace_t::global>> = std::string_view("global'");
template <> constexpr inline auto detail::reflect_owning<namespace_t::global> =
	detail::basic_namespace<namespace_t::global, get_type<append_pack<fundamental_type_pack,
	type_pack<X>>>,
	type_pack<overload::global_double_>>{};

namespace overload
{
	template <typename Overload, std::size_t Index>
	constexpr inline auto caster = nullptr;
}

namespace overload
{
	struct X_f {};
	template <>	constexpr inline auto caster<X_f, 0> = overload_member_caster<cv_qualifier::none, ref_qualifier::rvalue>;
	template <>	constexpr inline auto caster<X_f, 1> = overload_member_caster<cv_qualifier::none, ref_qualifier::lvalue>;

	struct X_operator_int {};
}

template <> constexpr inline auto detail::reflect_owning<detail::constructor_wrap<X>>
	= detail::basic_overloaded_constructor<X, type_pack<
		constructor_partial_info<false, const int&>,
		constructor_partial_info<true, const double&>>>{};

template <> constexpr inline auto detail::reflect_owning<detail::name_wrap<X>> = std::string_view("X");
template <> constexpr inline auto detail::reflect_owning<detail::id_wrap<X>> = std::size_t(1);
template <> constexpr inline auto detail::reflect_owning<X> = detail::basic_class_type<namespace_t::global, X,
	type_pack<
		overload::X_f,
		overload::X_operator_int>,
	type_pack<>>{};

template <> constexpr inline auto detail::reflect_owning<detail::name_wrap<overload::X_f>> = std::string_view("f");
template <> constexpr inline auto detail::reflect_owning<overload::X_f>
	= detail::basic_overloaded_member_function<overload::X_f, value_pack<
		overload::caster<overload::X_f, 0>(&X::f),
		overload::caster<overload::X_f, 1>(&X::f)>>{};

template <> constexpr inline auto detail::reflect_owning<value_t<overload::caster<overload::X_f, 0>(&X::f)>>
	= detail::basic_member_function<overload::X_f, overload::caster<overload::X_f, 0>(&X::f)>{};
template <> constexpr inline auto detail::reflect_owning<value_t<overload::caster<overload::X_f, 1>(&X::f)>>
	= detail::basic_member_function<overload::X_f, overload::caster<overload::X_f, 1>(&X::f)>{};

template <> constexpr inline auto detail::reflect_owning<detail::name_wrap<overload::X_operator_int>> = std::string_view("operator int");
template <> constexpr inline auto detail::reflect_owning<overload::X_operator_int>
	= detail::basic_overloaded_conversion_function<overload::X_operator_int, value_pack<
		&X::operator int>>{};

template <> constexpr inline auto detail::reflect_owning<value_t<&X::operator int>>
	= detail::basic_conversion_function<overload::X_operator_int, false, &X::operator int>{};


#include "../PP/PP/unique.hpp"
#include "../PP/PP/simple_vector.hpp"

int main()
{
	const type* X_ = reflect<namespace_t::global, namespace_t>().get_type("X");

	if (X_)
	{
		if (const overloaded_constructor* cs = X_->get_constructors(); cs)
		{
			for (const constructor& c : cs->get_overloads())
			{
				std::cout << c << std::boolalpha << "is explicit? " << c.is_explicit() << ".";
			}
		}
	}

	std::cout << "\n";

	PP::simple_vector<dynamic_object> objects;

	const overloaded_namespace_function* doubler = reflect<namespace_t::global, namespace_t>().get_function("double_");

	if (doubler)
	{
		objects.push_back(doubler->invoke({  7 }));
		objects.push_back(doubler->invoke({ 20 }));
		objects.push_back(doubler->invoke({ -5 }));

		const overloaded_member_function* ff = objects.begin()->get_type().get_member_function("f");

		bool x = true;

		for (dynamic_reference r : objects)
		{
			if (x)
				ff->invoke(r.move());
			else
				ff->invoke(r);

			x = !x;
		}
	}

	objects.clear();

	std::cout.flush();
	return 0;
}
