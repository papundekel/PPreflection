#include <iostream>

#include "PPreflection/reflect.hpp"

namespace N
{
	void print(int a)
	{
		std::cout << "int " << a << '\n';
	}
	void print(short b)
	{
		std::cout << "short " << b << '\n';
	}
}

#include "f.hpp"

#include "main.cpp.meta"

int main()
{
	const auto& n = *PPreflection::global_namespace.get_namespace("N");

	for (const auto& f : n.get_functions())
		std::cout << f << "\n";

	while (true)
	{
		int a;
		std::cin >> a;

		auto obj = PPreflection::dynamic_object::create_void();

		if (a > 5)
			obj = PPreflection::dynamic_object::create_copy(a % 2 == 0);
		else
			obj = PPreflection::dynamic_object::create_copy((short)a);

		n.invoke_qualified("print", { obj });
	}

	std::cout.flush();
	return 0;
}
