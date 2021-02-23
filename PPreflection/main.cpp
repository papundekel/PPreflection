#include <iostream>
#include "Namespace.hpp"
#include "dynamic_reference.hpp"
#include "types/types.hpp"
#include "reflect.hpp"
#include "value_tuple.hpp"

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
	using namespace_global = PPreflection::Namespace::global;
}

namespace PPreflection::tags::overloaded
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
template <> constexpr inline auto PPreflection::detail::metadata<namespace_global> = PPreflection::detail::basic_namespace<namespace_global>{};
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::types<PPreflection::Namespace::global>> = PP::type_tuple<S>;
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::namespaces<PPreflection::Namespace::global>> = PP::type_tuple<>;
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::functions<PPreflection::Namespace::global>> = PP::type_tuple<
//	PPreflection::tags::overloaded::f
//>;

// ::S
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<S>> = "S"_sv;
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<S>> = PP::type<namespace_global>;
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::nested_classes<S>> = PP::type_tuple<>;
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::base_classes<S>> = PP::type_tuple<>;
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::static_member_functions<S>> = PP::type_tuple<
//	PPreflection::tags::overloaded::S::g
//>;
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::member_functions<S>> = PP::type_tuple<
//	PPreflection::tags::overloaded::S::f
//>;

// ::S::S
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::constructors<S>> = detail::basic_overloaded_constructor<S>{};
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<tags::constructors<S>>> = PP::type_tuple<
//	PPreflection::tags::constructor<S>,
//	PPreflection::tags::constructor<S, int>
//>;

// ::S::S()
//

// ::S::S(int)
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::is_explicit<S, int>> = true;
//
// ::S::g
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloaded::S::g> = detail::basic_overloaded_static_member_function<reflection::overloaded::S::g>{};
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<reflection::overloaded::S::g>> = PP::string_view("g");
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<reflection::overloaded::S::g>> = PP::type<S>;
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<reflection::overloaded::S::g>> = PP::value_tuple<
// ::S::g
//>;

// ::S::g(int)
//template <> constexpr inline auto PPreflection::detail::metadata<PP::value_t<::S::g>> = detail::basic_static_member_function<::S::g>{};
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PP::value_t<::S::g>>> = PP::type<PPreflection::tags::overloaded::S::g>;

// ::S::f
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloaded::S::f> = detail::basic_overloaded_member_function<PPreflection::tags::overloaded::S::f>{};
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<PPreflection::tags::overloaded::S::f>> = PP::string_view("f");
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<PPreflection::tags::overloaded::S::f>> = PP::type<S>;
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PPreflection::tags::overloaded::S::f>> = PP::value_tuple<
//	&::S::f
//>;

// ::S::f(int) const
//template <> constexpr inline auto PPreflection::detail::metadata<PP::value_t<&::S::f>> = detail::basic_member_function<&::S::f>{};
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PP::value_t<&::S::f>>> = PP::type<PPreflection::tags::overloaded::S::f>;

// ::S::operator int
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::conversion_function<::S, int>> = detail::basic_overloaded_conversion_function<::S, int>{};
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PPreflection::tags::conversion_function<::S, int>> = PP::value_tuple<
//	&::S::operator int
//>;

// ::S::operator int() const
//template <> constexpr inline auto PPreflection::detail::metadata<PP::value_t<&::S::operator int>> = detail::basic_conversion_function<&::S::operator int>{};
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PP::value_t<&::S::operator int>>> = PP::type<PPreflection::tags::conversion_function<::S, int>>;
//template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::is_explicit<PP::value_t<&::S::operator int>>> = false;

// ::f
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloaded::f> = detail::basic_overloaded_namespace_function<PPreflection::tags::overloaded::f>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<PPreflection::tags::overloaded::f>> = "f"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<PPreflection::tags::overloaded::f>> = PP::type<namespace_global>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PPreflection::tags::overloaded::f>> = PP::value_tuple<
	::f
>;

// ::f()
template <> constexpr inline auto PPreflection::detail::metadata<PP::value_t<::f>> = detail::basic_namespace_function<::f>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::overloads<PP::value_t<::f>>> = PP::type<PPreflection::tags::overloaded::f>;

int main()
{
	const PPreflection::function& _f = PPreflection::reflect(PP::value<::f>);

	//_f.invoke({ 5 });

	std::cout.flush();
	return 0;
}
