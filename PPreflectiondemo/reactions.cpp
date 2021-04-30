#include "reactions.hpp"

#include <iostream>

int animals::value = -1;

static constexpr bool print = false;

void
reactions::react_to([[maybe_unused]] const animals::ape& ape)
{
	if constexpr (print)
		std::cout << "smile at " << ape.name() << '\n';
	else
		animals::value = 0;
}

void
reactions::react_to([[maybe_unused]] const animals::bat& bat)
{
	if constexpr (print)
		std::cout << "kill " << bat.name() << '\n';
	else
		animals::value = 1;
}

void
reactions::react_to([[maybe_unused]] const animals::cat& cat)
{
	if constexpr (print)
		std::cout << "pet " << cat.name() << '\n';
	else
		animals::value = 2;
}

void
reactions::react_to([[maybe_unused]] const animals::dog& dog)
{
	if constexpr (print)
		std::cout << "run from " << dog.name() << '\n';
	else
		animals::value = 3;
}

void
reactions::react_to([[maybe_unused]] const animals::elk& elk)
{
	if constexpr (print)
		std::cout << "hunt " << elk.name() << '\n';
	else
		animals::value = 4;
}
