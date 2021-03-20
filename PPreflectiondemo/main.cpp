#include <iostream>

#include "PPreflection/reflect.hpp"

void print_int(int a)
{
	std::cout << a << '\n';
}

#include "f.hpp"

void print_enum(G::E e)
{
	switch(e)
	{
	case G::a:
		std::cout << "a"; break;
	case G::tinko:
		std::cout << "tinko"; break;
	case G::cigi:
		std::cout << "cigi"; break;
	case G::bugi:
		std::cout << "bugi"; break;
	}

	std::cout << '\n';
}

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

	auto& e = PPreflection::type::reflect(PP::type<G::E>);
	for (auto& v : e.get_values())
		gn.invoke_qualified("print_enum", { v.get_value() });

	for (auto& v : e.get_values())
		std::cout << v << '\n';

	auto vp = PPreflection::dynamic_object::create(PP::type<void*>, nullptr);

	std::cout << vp.get_type() << '\n';

	auto cvp = PP::move(vp).cast(PPreflection::type::reflect(PP::type<const void*>));

	std::cout << cvp.get_type() << '\n';

	std::cout.flush();
	return 0;
}
