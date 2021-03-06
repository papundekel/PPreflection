#include <iostream>

#include "PP/value_tuple.hpp"

#include "PPreflection/dynamic_reference.hpp"
#include "PPreflection/Namespace.hpp"
#include "PPreflection/overload_cast.h"
#include "PPreflection/reflect.hpp"
#include "PPreflection/types/types.hpp"

class S
{
public:
	S()
	{
		std::cout << "S()\n";
	}
	explicit S(int a)
	{
		std::cout << "S(" << a << ")\n";
	}
	~S()
	{
		std::cout << "~S()\n";
	}

	void f(int a) const
	{
		std::cout << "S::f(" << a << ")\n";
	}

	static void g(int a)
	{
		std::cout << "S::g(" << a << ")\n";
	}

	operator int() const
	{
		return 5;
	}
};

enum E
{
	val = -8,
	cigi
};

void f(int a)
{
	std::cout << "f(" << a << ")\n";
}
void f(int a, int b)
{
	std::cout << "f(" << a << ", " << b << ")\n";
}

namespace PPreflection::tags::global
{
	namespace S
	{
		class f;
		class g;
	}

	class f;
}

// ::
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::types<PPreflection::Namespace::global>> = PP::type_tuple<
	::S
>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::namespaces<PPreflection::Namespace::global>> = PP::type_tuple<>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::functions<PPreflection::Namespace::global>> = PP::type_tuple<
	PPreflection::tags::global::f
>;

// ::E
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<::E>> = "E"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<::E>> = PP::type<PPreflection::Namespace::global>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::enum_values<::E>> = PP::value_tuple<
	E::val,
	E::cigi
>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<PP::value_t<::E::val>>> = "val"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<PP::value_t<::E::cigi>>> = "cigi"_sv;

// ::S
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<::S>> = "S"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<::S>> = PP::type<PPreflection::Namespace::global>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::nested_classes<::S>> = PP::type_tuple<>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::base_classes<::S>> = PP::type_tuple<>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::static_member_functions<::S>> = PP::type_tuple<
	PPreflection::tags::global::S::g
>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::member_functions<::S>> = PP::type_tuple<
	PPreflection::tags::global::S::f,
	PPreflection::tags::conversion_function<::S, int>
>;

// ::S::S
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PPreflection::tags::constructors<::S>>> = PP::type_tuple<
	PPreflection::tags::constructor<::S>,
	PPreflection::tags::constructor<::S, int>
>;
// ::S::S()
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::constructor<::S>> = PPreflection::detail::basic_constructor<::S>{};
// ::S::S(int)
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::is_explicit<::S, int>> = PP::value_true;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::constructor<::S, int>> = PPreflection::detail::basic_constructor<::S, int>{};

// ::S::g
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::global::S::g> = detail::basic_overloaded_static_member_function<PPreflection::tags::global::S::g>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<PPreflection::tags::global::S::g>> = "g"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<PPreflection::tags::global::S::g>> = PP::type<::S>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PPreflection::tags::global::S::g>> = PP::value_tuple<
	::S::g
>;
// ::S::g(int)
template <> constexpr inline auto PPreflection::detail::metadata<PP::value_t<::S::g>> = detail::basic_static_member_function<::S::g>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PP::value_t<::S::g>>> = PP::type<PPreflection::tags::global::S::g>;

// ::S::f
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::global::S::f> = detail::basic_overloaded_non_conversion_member_function<PPreflection::tags::global::S::f>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<PPreflection::tags::global::S::f>> = "f"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<PPreflection::tags::global::S::f>> = PP::type<S>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PPreflection::tags::global::S::f>> = PP::value_tuple<
	&::S::f
>;
// ::S::f(int) const
template <> constexpr inline auto PPreflection::detail::metadata<PP::value_t<&::S::f>> = detail::basic_non_conversion_member_function<&::S::f>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PP::value_t<&::S::f>>> = PP::type<PPreflection::tags::global::S::f>;

// ::S::operator int
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::conversion_function<::S, int>> = detail::basic_overloaded_conversion_function<::S, int>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PPreflection::tags::conversion_function<::S, int>>> = PP::value_tuple<
	&::S::operator int
>;
// ::S::operator int() const
template <> constexpr inline auto PPreflection::detail::metadata<PP::value_t<&::S::operator int>> = detail::basic_conversion_function<&::S::operator int>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PP::value_t<&::S::operator int>>> = PP::type<PPreflection::tags::conversion_function<::S, int>>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::is_explicit<PP::value_t<&::S::operator int>>> = false;

// ::f
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::global::f> = detail::basic_overloaded_namespace_function<PPreflection::tags::global::f>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<PPreflection::tags::global::f>> = "f"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<PPreflection::tags::global::f>> = PP::type<PPreflection::Namespace::global>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PPreflection::tags::global::f>> = PP::value_tuple<
	PPreflection::overload_caster<int>(::f),
	PPreflection::overload_caster<int, int>(::f)
>;
// ::f(int)
template <> constexpr inline auto PPreflection::detail::metadata<PP::value_t<PPreflection::overload_caster<int>(::f)>> = detail::basic_namespace_function<PPreflection::overload_caster<int>(::f)>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PP::value_t<PPreflection::overload_caster<int>(::f)>>> = PP::type<PPreflection::tags::global::f>;
// ::f(int, int)
template <> constexpr inline auto PPreflection::detail::metadata<PP::value_t<PPreflection::overload_caster<int, int>(::f)>> = detail::basic_namespace_function<PPreflection::overload_caster<int, int>(::f)>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PP::value_t<PPreflection::overload_caster<int, int>(::f)>>> = PP::type<PPreflection::tags::global::f>;

void xxxn() noexcept
{

}

int main()
{
	PPreflection::dynamic_reference r_xxxn = xxxn;
	
	auto& r_xxxn_type = dynamic_cast<const PPreflection::function_type&>(r_xxxn.get_type().remove_reference().type);
	
	auto p_xxxn = r_xxxn_type.function_to_pointer_conversion()(r_xxxn);
	
	auto& p_xxxn_type = dynamic_cast<const PPreflection::pointer_type&>(p_xxxn.get_cv_type().type);
	
	auto p_xxx = p_xxxn_type.function_pointer_conversion()(p_xxxn);
	
	std::cout << r_xxxn.get_type() << '\n';
	std::cout << p_xxxn.get_cv_type() << '\n';
	std::cout << p_xxx.get_cv_type() << '\n';

	const int a[2]{1, 5};

	PPreflection::dynamic_reference r_a = a;

	PPreflection::array_type_reference r_a_type = dynamic_cast<const PPreflection::object_type&>(r_a.get_type().remove_reference().type);

	auto p_a = r_a_type.array_to_pointer_conversion()(r_a);

	std::cout << r_a.get_type() << '\n';
	std::cout << p_a.get_type() << '\n';

	auto x = PPreflection::float_type.create_instance();

	auto& x_type = dynamic_cast<const PPreflection::arithmetic_type&>(x.get_cv_type().type);

	const auto y = x_type.promotion()(x);

	std::cout << x.get_cv_type() << '\n';
	std::cout << y.get_cv_type() << '\n';

	std::cout.flush();
	return 0;
}
