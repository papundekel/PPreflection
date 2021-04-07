#include <iostream>

#include "PPreflection/reflect.hpp"

namespace N
{
	void print(const int& x)
	{
		std::cout << x << "a\n";
	}
	void print(int& x)
	{
		std::cout << x << "b\n";
	}
}

#include "f.hpp"

#include "main.cpp.meta"

int main()
{
	const auto& n = *PPreflection::global_namespace.get_namespace("N");

	for (const auto& f : n.get_functions())
		std::cout << f << "\n";

	int a = 3;
	n.invoke_qualified("print", { a });
	n.invoke_qualified("print", { 5 });

	std::cout.flush();
	return 0;
}
