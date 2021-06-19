#include "visitor_reflection.hpp"

#include "reactions.hpp"

#include "visitor_reflection.cpp.meta"

#ifndef PPREFLECTOR_GUARD

#include <iostream>

namespace
{
	auto visitor_reflection_make_viables()
	{
		const auto& n =
			*PPreflection::global_namespace.get_namespace("reactions");

		return PPreflection::viable_functions(
			PPreflection::candidate_functions(n.get_functions())
				.trim_by_name("react_to")
				.trim_by_exact_argument_count(1),
			PP::type_tuple<const animals::ape&>,
			PP::type_tuple<const animals::bat&>,
			PP::type_tuple<const animals::cat&>,
			PP::type_tuple<const animals::dog&>,
			PP::type_tuple<const animals::elk&>);
	}
}

void visitors::visitor_reflection::react_to(const animals::animal& animal)
{
	static const auto viables = visitor_reflection_make_viables();

	viables.invoke({PPreflection::dynamic_polymorphic_reference(animal)});
}

#endif
