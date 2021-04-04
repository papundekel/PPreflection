#include <iostream>

#include "PPreflection/reflect.hpp"

namespace N
{
	void print(void* x)
	{
		std::cout << "void* " << x << '\n';
	}
	void print(int& x)
	{
		x = 7;
	}
}

#include "f.hpp"

#include "main.cpp.meta"

int main()
{
	const auto& n = *PPreflection::global_namespace.get_namespace("N");

	for (const auto& f : n.get_functions())
		std::cout << f << "\n";

	int x = 0;

	n.invoke_qualified("print", { x });

	std::cout << x << '\n';

	std::cout.flush();
	return 0;
}
