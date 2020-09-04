# PPreflection

C++ reflection knižnica.

Ročníkový projekt.

## Popis

C++20

Dve časti: generátor a framework.

### Generátor

Súčasťou knižnice bude generátor metadát. Ten vygeneruje zo zdrojového kódu užívateľa potrebné metadáta pre reflexiu. Metadáta sú C++ kód, ktorý bude súčasťou kompilovaného kódu.

Cieľom je možnosť zapojiť generátor do automatizovaného buildu s čo najmenšou prácou užívateľa: zdrojový kód prejde cez generátor, ktorý vyprodukuje kód aj s metadátami; ten dostane kompilátor.

Najjednoduchšie bude použiť clang nástroje, ktoré sprístupňujú AST. Iná možnosť by bola iba napísať vlastný parser.

### Framework

Poskytuje rozhranie pre prístup k metadátam.

Triedy ako napr. `type` a `function` s metódami `is_derived_from(/*iný typ*/)` a `invoke(/*dynamické argumenty*/)` resp.

Rieši úlohy ako: reprezentácia metadát, dynamicky vytvorené objekty cez reflexiu, implementácia pravidiel inicializácie a overload resolution.

## Rozsah práce

Keďže potenciálny rozsah podporovaných funckcií končí pri implementácii prakticky celého kompilátora, cieľom tejto knižnice zatiaľ **nie** je podporovať vytváranie nových tried, funckií a pod.

V aktuálnom stave vývoja sa javí ako rozsahovo rozumné implementovať iba dynamické volanie funkcií a spôsoby, ktorými sa tieto funkcie dajú "objaviť" (získať členské metódy danej triedy, získať funkcie s počtom parametrov 2 v danom namespace a pod.).

## Príklad

```cpp
// declarations.hpp
struct X
{
	int x;

	X(const int& x);

	explicit X(const double& y);

	X(int a, int b);

	void f() &;
	void f() &&;

	explicit operator int();
	operator int() const;

	~X();
};

// main.cpp
#include "declarations.hpp"
// #include "framework.hpp"

// generated
namespace reflect_detail
{
	struct X_f {};
	struct global_double_ {};
}

template <> constexpr inline auto detail::reflect_metadata<detail::name_wrap<namespace_t::global>>
	= std::string_view("global'");
template <> constexpr inline auto detail::reflect_metadata<namespace_t::global> =
	detail::basic_namespace<namespace_t::global, append_pack<fundamental_type_pack,
		type_pack<X>>,
		type_pack<reflect_detail::global_double_>>{};

template <> constexpr inline auto detail::reflect_metadata<detail::name_wrap<X>> = std::string_view("X");
template <> constexpr inline auto detail::reflect_metadata<detail::id_wrap<X>> = std::size_t(0);
template <> constexpr inline auto detail::reflect_metadata<X>
	= detail::basic_class_type<namespace_t::global, X,
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
	template <>	constexpr inline auto overload_caster<reflect_detail::X_f, 0>
		= overload_member_caster<cv_qualifier::none, ref_qualifier::rvalue>(&X::f);
	template <>	constexpr inline auto overload_caster<reflect_detail::X_f, 1>
		= overload_member_caster<cv_qualifier::none, ref_qualifier::lvalue>(&X::f);
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

template <> constexpr inline auto detail::reflect_metadata<detail::name_wrap<reflect_detail::global_double_>>
	= std::string_view("double_");
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

// /generated

int main()
{
	

	return 0;
}
```
