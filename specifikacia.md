# PPreflection

C++ reflection knižnica.

Bakalárska práca.

## Popis

C++20

Dve časti: generátor a framework.

### Generátor

Súčasťou knižnice bude generátor metadát. Ten vygeneruje zo zdrojového kódu užívateľa potrebné metadáta pre reflexiu. Metadáta sú C++ kód, ktorý bude súčasťou kompilovaného kódu.

Cieľom je možnosť zapojiť generátor do automatizovaného buildu s čo najmenšou prácou užívateľa: zdrojový kód prejde cez generátor, ktorý vyprodukuje kód aj s metadátami; ten dostane kompilátor.

### Framework

Poskytuje rozhranie pre prístup k metadátam.

Triedy ako napr. `type` a `function` s metódami `is_derived_from(/*iný typ*/)` a `invoke(/*dynamické argumenty*/)` resp.

Rieši úlohy ako: reprezentácia metadát, dynamicky vytvorené objekty cez reflexiu, implementácia pravidiel inicializácie a overload resolution.

## Príklad

```cpp
// declarations.hpp
#include <string_view>

struct X
{
	void f(std::string_view);
	~X();
};

// implementations.cpp
#include "declarations.hpp"
#include <iostream>

void X::f(std::string_view s)
{
	std::cout << "hello world, " << s << '\n';
}

X::~X()
{
	std::cout << "~X()\n";
}

// main.cpp
#include "declarations.hpp"

int main()
{
	if (auto* X_ = reflect<namespace_t::global, namespace_t>().get_type("X"); X_)
	{
		auto x = X_->create_instance();
		if (auto* f_ = x.get_type().get_member_function("f"); f_)
			f_->invoke(x, "abc");
	}

	return 0;
}
```

#### Výstup
```
hello world, abc
~X()

```