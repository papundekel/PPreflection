#include "visitor_reflection.hpp"

#include "reactions.hpp"

#include "visitor_reflection.cpp.meta"

#ifndef PPREFLECTOR_GUARD

#include <iostream>

namespace
{
	// auto visitor_reflection_make_viables()
	//{
	//	const auto& n =
	//		*PPreflection::global_namespace.get_namespace("reactions");
	//
	//	return PPreflection::viable_functions(
	//		PPreflection::candidate_functions(n.get_functions())
	//			.trim_by_name("react_to")
	//			.trim_by_exact_argument_count(1),
	//		PP::type_tuple<const animals::ape&>,
	//		PP::type_tuple<const animals::bat&>,
	//		PP::type_tuple<const animals::cat&>,
	//		PP::type_tuple<const animals::dog&>,
	//		PP::type_tuple<const animals::elk&>);
	//}
}

// constexpr int f()
//{
//	auto o = PPreflection::dynamic_object::create(PP::type<int>, 5);
//
//	PPreflection::dynamic_reference r = o;
//
//	return r.cast_unsafe(PP::type<int&>);
//}
//
//[[maybe_unused]] constexpr auto x = f();

void visitors::visitor_reflection::react_to(const animals::animal& animal)
{
	// static const auto viables = visitor_reflection_make_viables();

	// viables.invoke({PPreflection::dynamic_polymorphic_reference(animal)});

	// equivalent to

	PPreflection::global_namespace.get_namespace("reactions")
		->invoke_qualified(
			"react_to",
			{PPreflection::dynamic_polymorphic_reference(animal)});
}

#endif
