#include "reactions.hpp"

#include <iostream>

static constexpr bool print = true;

void reactions::react_to([[maybe_unused]] const animals::ape& ape)
{
	if constexpr (print)
		std::cout << "smile at " << ape.name() << '\n';
}

void reactions::react_to([[maybe_unused]] const animals::bat& bat)
{
	if constexpr (print)
		std::cout << "kill " << bat.name() << '\n';
}

void reactions::react_to([[maybe_unused]] const animals::cat& cat)
{
	if constexpr (print)
		std::cout << "pet " << cat.name() << '\n';
}

void reactions::react_to([[maybe_unused]] const animals::dog& dog)
{
	if constexpr (print)
		std::cout << "run from " << dog.name() << '\n';
}

void reactions::react_to([[maybe_unused]] const animals::elk& elk)
{
	if constexpr (print)
		std::cout << "hunt " << elk.name() << '\n';
}
