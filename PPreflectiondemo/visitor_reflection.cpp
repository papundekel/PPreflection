#include "visitor_reflection.hpp"

#include "PPreflection/PPreflection.hpp"

#include "reactions.hpp"

#include "visitor_reflection.cpp.meta"

#ifndef PPREFLECTOR_GUARD

void visitors::visitor_reflection::react_to(const animals::animal& animal)
{
	PPreflection::global_namespace.get_namespace("reactions")->
		invoke_qualified("react_to", { PPreflection::dynamic_polymorphic_reference(animal) });
}

#endif
