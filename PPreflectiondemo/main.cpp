#include <iostream>

#include "PPreflection/reflect.hpp"

void print_int(int a)
{
	std::cout << a << '\n';
}

#include "f.hpp"
#include "main.cpp.meta"

int main()
{
	
	auto& gn = PPreflection::global_namespace;

	auto& Mn = *gn.get_namespace("M");

	auto a = Mn.invoke_qualified("f", { 1 });
	auto b = Mn.invoke_qualified("f", { 1, a });

	gn.invoke_qualified("print_int", { a });
	gn.invoke_qualified("print_int", { b });
	//

	// equivalent
	
	//
	auto aa = M::f(1);
	auto bb = M::f(1, aa);

	print_int(aa);
	print_int(bb);
	//

	std::cout.flush();
	return 0;
}
