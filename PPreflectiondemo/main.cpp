#include <iostream>

#include "PPreflection/reflect.hpp"

void print_int(int a)
{
	std::cout << a << '\n';
}
void print_bool(bool b)
{
	std::cout << std::boolalpha << b << '\n';
}

#include "f.hpp"

#include "main.cpp.meta"

int main()
{
	PPreflection::global_namespace.invoke_qualified("print_bool", { true });

	std::cout.flush();
	return 0;
}
