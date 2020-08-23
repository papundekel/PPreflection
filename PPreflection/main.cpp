#include <iostream>
#include <variant>

#include "get_value.hpp"

#include "value_pack.h"
#include "apply_pack.h"
#include "map_pack.h"
#include "append_pack.h"
#include "overload_cast.h"


#include "unique_pointer.hpp"
#include "simple_vector.hpp"
#include "to_chars.hpp"

#include "simple_ostream.hpp"
#include "array_ostream.hpp"
#include "string_ostream.hpp"

#include "cref_t.hpp"
#include "simple_range.hpp"
#include "dynamic_ref.hpp"
#include "dynamic_object.hpp"

#include "function.hpp"
#include "type.hpp"
#include "member_function.hpp"
#include "member_like_function.hpp"
#include "namespace_function.hpp"
#include "namespace_t.hpp"
#include "conversion_function.hpp"
#include "one_parameter_constructor.hpp"

#include "overloaded_function.hpp"
#include "overloaded_member_function.hpp"
#include "descriptor.hpp"

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

#include "array_vector.hpp"
#include "unique_raw_pointer.hpp"
#include "dynamic_block.hpp"

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

struct convertor
{
	std::variant<const conversion_function*, const one_parameter_constructor*> ptr;

	dynamic_object convert(const dynamic_reference& arg)
	{
		return std::visit(
			[&arg](const auto* x)
			{
				return x->invoke(arg);
			}, ptr);
	}
};

int main()
{
	simple_vector<dynamic_object> objects;

	auto* doubler = reflect<namespace_t::global, namespace_t>().get_function("double_");

	if (doubler)
	{
		objects.push_back(doubler->invoke({  7 }));
		objects.push_back(doubler->invoke({ 20 }));
		objects.push_back(doubler->invoke({ -5 }));

		for (auto&& o : objects)
			std::cout << o.operator dynamic_reference().cast<const X&>().x << '\n';
	}

	objects.clear();

	std::cout.flush();
	return 0;
}
