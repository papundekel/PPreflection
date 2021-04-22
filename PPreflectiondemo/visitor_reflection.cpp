#include "visitor_reflection.hpp"

#include "PPreflection/PPreflection.hpp"

#include "reactions.hpp"

#include "visitor_reflection.cpp.meta"

namespace
{
	auto visitor_reflection_make_viables()
	{
		const auto& n = *PPreflection::global_namespace.get_namespace("reactions");

		PPreflection::candidate_functions candidates(n.get_functions());

		candidates.trim_name("react_to").trim_exact_argument_count(1);

		using argument_lists_type = std::initializer_list<std::initializer_list<PP::ref_wrap<const PPreflection::reference_type&>>>;

		return PPreflection::viable_functions(candidates.get_functions_view(),
			argument_lists_type
			{
				{PPreflection::reflect(PP::type<const animals::ape&>)},
				{PPreflection::reflect(PP::type<const animals::bat&>)},
				{PPreflection::reflect(PP::type<const animals::cat&>)},
				{PPreflection::reflect(PP::type<const animals::dog&>)},
				{PPreflection::reflect(PP::type<const animals::elk&>)},
			});
	}
}

void visitors::visitor_reflection::react_to(const animals::animal& animal)
{
	static const auto viables = visitor_reflection_make_viables();
	
	viables.invoke({ PPreflection::dynamic_polymorphic_reference(animal) });
}
