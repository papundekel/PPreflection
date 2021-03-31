# PPreflection

C++ reflection knižnica.

Bakalárska práca.

# Idea

## Definícia

Reflexia je schopnosť jazyka explicitne sa odkazovať na vlastnú štruktúru.

### Príklad z C++:

Štruktúra: funkcie patria do namespace-ov.\
Táto štruktúra má implicitný vplyv na výsledný program, keďže ovplyvňuje pravidlá pri výbere overloadu funkcie pri volaní.\
Ale, nikde v kóde sa nevieme explicitne odkázať, napríklad, na zoznam všetkých funkcií v danom namespace, pretože v tomto zmysle C++ reflexiu nepodporuje.

## Hlavné myšlienky

* rozšíriť C++20 o reflexiu
* nevytvárať nový prekladač
* nerozširovať kód už existujúceho prekladača
* umožniť dynamické volanie funkcií, vrátane "overload resolution" a "implicit conversions"
* implementovať potenciálne veľmi malú, ale čo najviac ucelenú podmnožinu jazyka

### Záver

Implementovať reflexiu v dvoch častiach, generátor a framework.

#### Generátor
Generátor je Clang plugin, ktorý vygeneruje z prekladovej jednotky súbor s metadátami.\
Metadáta sú platný C++ kód, pripoja sa do užívateľovho programu cez `#include`.

#### Framework
Framework je obyčajná C++ knižnica, ktorú užívateľ pripojí k svojmu programu.

Toto rozdelenie síce vyžaduje implementáciu pluginu špecifického prekladača,
ale keďže metadáta sú obyčajný C++ kód, užívateľ môže po generácii svoj program prekladať ľubovoľným prekladačom, ktorý podporuje danú verziu C++ štandardu.\
Clang teda slúži v podstate len ako knižnica pre generátor.

Užívateľ potrebuje linknúť framework, include-núť jeden header z knižnice a do build systému pridať ekvivalent tohto pseudo-pravidla:\
`@.cpp.meta <- clang++ -fplugin="$PPREFLECTOR_PATH" -fsyntax-only @.cpp`

# Implementácia

## Framework

Framework implementuje dynamické typy, teda typy ako objekty.

```cpp
namespace N { class X; }
const type* t = nullptr;
t = &PPreflection::reflect(PP::type<int>);
std::cout << *t << "\n"; // prints "int"
t = &PPreflection::reflect(PP::type<X>);
std::cout << *t << "\n"; // prints "::N::X"
```

S dynamickými typmi implementuje aj dynamicky typované premenné (napríklad return z dynamicky volanej funkcie)

Pre volanie funkcií tiež potrebuje implementovať overload resolution, implicitné konverzie a inicializáciu.

```cpp
void f(int a) { std::cout << a; }
void f(std::nullptr_t) { std::cout << "null"; }

PP::string_view function_name = "f";

auto x = PPreflection::dynamic_object::create_copy('A');
PPreflection::global_namespace.invoke(function_name, x); // prints "65"

x = PPreflection::dynamic_object::create_copy(nullptr);
PPreflection::global_namespace.invoke(function_name, x); // prints "null"
```

### Hierarchia tried
[odkaz](class_diagram.svg)

## Generátor

Clang plugin.

Z AST vygeneruje všetky potrebné informácie pre reflexiu, ktoré nie sú v jazyku dostupné.\
Tieto informácie zachytí ako explicitné špecializácie constexpr inline premennej.

Napríklad pre namespace:

```cpp
template <> constexpr inline auto PPreflection::detail::metadata<N> = PPreflection::detail::basic_namespace<N>{};
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<N>> = "N"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::parent<N>> = PP::type<parent>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::types<N>> = PP::type_tuple<types...>;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::namespaces<N>> = PP::type_tuple<namespaces...>;
```

# Príklad

```cpp
// declarations.hpp
namespace N
{
	int f(int a);
	int f(bool a);
}
```

```cpp
// main.cpp
#include "PPreflection/reflect.hpp"

#include "declarations.hpp"

#include "main.cpp.meta"

int main()
{
	const auto* n = PPreflection::global_namespace.get_namespace("N");
	
	if (n)
	{
		// prints
		// void ::N::f(int)
		// void ::N::f(bool)
		for (const auto& f : n->get_functions())
			std::cout << f << "\n";

		auto r1 = n->invoke("f", { short(2) }); //calls N::f(int)
		auto r2 = n->invoke("f", { &n }); //calls N::f(bool)
		auto r3 = n->invoke("f", { nullptr }); // invalid call
		auto r4 = n->invoke("f", { 5, 2 }); // invalid call
		auto r5 = n->invoke("g"); // invalid call
	}

	std::cout.flush();
	return 0;
}
```
