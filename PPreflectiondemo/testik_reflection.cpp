#include "testik.hpp"

#include "testik_reflection.cpp.meta"

#ifndef PPREFLECTOR_GUARD

#include <iostream>

void N::g()
{
	PPreflection::global_namespace.get_namespace("N")->invoke_qualified("f",
	                                                                    {D()});
}

#endif
