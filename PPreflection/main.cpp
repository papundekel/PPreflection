#include <iostream>
//#include "Namespace.hpp"
//#include "reflect.hpp"
//#include "dynamic_variable.hpp"
/*
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

void f(int a)
{
	std::cout << "f(" << a << ")\n";
}

namespace
{
	using namespace_global = Namespace::global;
}

namespace reflection::overloaded
{
	namespace S
	{
		struct f {};
		struct g {};
		struct op_int {};
	}

	struct f {};
}

using namespace std::literals::string_view_literals;

// ::
template <> constexpr inline auto reflection::metadata<Namespace::global> = detail::basic_namespace<namespace_global>{};
template <> constexpr inline auto reflection::metadata<reflection::types<Namespace::global>> = PP::type_tuple_v<S>;
template <> constexpr inline auto reflection::metadata<reflection::namespaces<Namespace::global>> = PP::type_tuple_v<>;
template <> constexpr inline auto reflection::metadata<reflection::functions<Namespace::global>> = PP::type_tuple_v<
	reflection::overloaded::f
>;

// ::S
template <> constexpr inline auto reflection::metadata<reflection::name<S>> = "S"sv;
template <> constexpr inline auto reflection::metadata<reflection::parent<S>> = PP::type<namespace_global>;
template <> constexpr inline auto reflection::metadata<reflection::nested_classes<S>> = PP::type_tuple_v<>;
template <> constexpr inline auto reflection::metadata<reflection::base_classes<S>> = PP::type_tuple_v<>;
template <> constexpr inline auto reflection::metadata<reflection::static_member_functions<S>> = PP::type_tuple_v<
	reflection::overloaded::S::g
>;
template <> constexpr inline auto reflection::metadata<reflection::member_functions<S>> = PP::type_tuple_v<
	reflection::overloaded::S::f
>;

// ::S::S
template <> constexpr inline auto reflection::metadata<reflection::constructors<S>> = detail::basic_overloaded_constructor<S>{};
template <> constexpr inline auto reflection::metadata<reflection::overloads<reflection::constructors<S>>> = PP::type_tuple_v<
	reflection::constructor<S>,
	reflection::constructor<S, int>
>;

// ::S::S()
//

// ::S::S(int)
template <> constexpr inline auto reflection::metadata<reflection::is_explicit<S, int>> = true;

// ::S::g
template <> constexpr inline auto reflection::metadata<reflection::overloaded::S::g> = detail::basic_overloaded_static_member_function<reflection::overloaded::S::g>{};
template <> constexpr inline auto reflection::metadata<reflection::name<reflection::overloaded::S::g>> = "g"sv;
template <> constexpr inline auto reflection::metadata<reflection::parent<reflection::overloaded::S::g>> = PP::type<S>;
template <> constexpr inline auto reflection::metadata<reflection::overloads<reflection::overloaded::S::g>> = PP::type_tuple_v<
	PP::value_t<::S::g>
>;

// ::S::g(int)
template <> constexpr inline auto reflection::metadata<PP::value_t<::S::g>> = detail::basic_static_member_function<::S::g>{};
template <> constexpr inline auto reflection::metadata<reflection::overloads<PP::value_t<::S::g>>> = PP::type<reflection::overloaded::S::g>;

// ::S::f
template <> constexpr inline auto reflection::metadata<reflection::overloaded::S::f> = detail::basic_overloaded_member_function<reflection::overloaded::S::f>{};
template <> constexpr inline auto reflection::metadata<reflection::name<reflection::overloaded::S::f>> = "f"sv;
template <> constexpr inline auto reflection::metadata<reflection::parent<reflection::overloaded::S::f>> = PP::type<S>;
template <> constexpr inline auto reflection::metadata<reflection::overloads<reflection::overloaded::S::f>> = PP::type_tuple_v<
	PP::value_t<&::S::f>
>;

// ::S::f(int) const
template <> constexpr inline auto reflection::metadata<PP::value_t<&::S::f>> = detail::basic_member_function<&::S::f>{};
template <> constexpr inline auto reflection::metadata<reflection::overloads<PP::value_t<&::S::f>>> = PP::type<reflection::overloaded::S::f>;

// ::S::operator int
//template <> constexpr inline auto reflection::metadata<reflection::conversion_function<::S, int>> = detail::basic_overloaded_conversion_function<::S, int>{};
//template <> constexpr inline auto reflection::metadata<reflection::overloads<reflection::conversion_function<::S, int>> = PP::type_tuple_v<
//	PP::value_t<&::S::operator int>
//>;

// ::S::operator int() const
//template <> constexpr inline auto reflection::metadata<PP::value_t<&::S::operator int>> = detail::basic_conversion_function<&::S::operator int>{};
//template <> constexpr inline auto reflection::metadata<reflection::overloads<PP::value_t<&::S::operator int>>> = PP::type<reflection::conversion_function<::S, int>>;
//template <> constexpr inline auto reflection::metadata<reflection::is_explicit<PP::value_t<&::S::operator int>>> = false;

// ::f
template <> constexpr inline auto reflection::metadata<reflection::overloaded::f> = detail::basic_overloaded_namespace_function<reflection::overloaded::f>{};
template <> constexpr inline auto reflection::metadata<reflection::name<reflection::overloaded::f>> = "f"sv;
template <> constexpr inline auto reflection::metadata<reflection::parent<reflection::overloaded::f>> = PP::type<namespace_global>;
template <> constexpr inline auto reflection::metadata<reflection::overloads<reflection::overloaded::f>> = PP::type_tuple_v<
	PP::value_t<::f>
>;

// ::f()
template <> constexpr inline auto reflection::metadata<PP::value_t<::f>> = detail::basic_namespace_function<::f>{};
template <> constexpr inline auto reflection::metadata<reflection::overloads<PP::value_t<::f>>> = PP::type<reflection::overloaded::f>;
*/

int main()
{
	

	std::cout.flush();
	return 0;
}
