#include "testik.hpp"

#include "testik_reflection.cpp.meta"

#ifndef PPREFLECTOR_GUARD

#include <iostream>

void N::g()
{
	for (auto& n : PPreflection::type::reflect(PP::type<S>)
					   .get_parent()
					   .as_namespace()
					   ->get_namespaces())
		std::cout << n << '\n';

	PPreflection::global_namespace.get_namespace("N")->invoke_qualified("f",
																		{D()});
}

#endif
