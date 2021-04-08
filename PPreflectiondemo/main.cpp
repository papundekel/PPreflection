#include <iostream>

#include "PPreflection/reflect.hpp"

namespace N
{
	struct B
	{
		void f() const
		{
			std::cout << "f";
		}
	};
	struct D : public B{};
	
	void print(const B& x)
	{
		x.f();
		std::cout << "\n";
	}
	void print(const D& x)
	{
		x.f();
		x.f();
		std::cout << "\n";
	}
}

#include "f.hpp"

#include "main.cpp.meta"

int main()
{
	const auto& n = *PPreflection::global_namespace.get_namespace("N");

	for (const auto& f : n.get_functions())
		std::cout << f << "\n";

	N::B b;
	N::D d;
	n.invoke_qualified("print", { b });
	n.invoke_qualified("print", { d });

	std::cout.flush();
	return 0;
}
