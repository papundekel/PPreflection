#include "visitor_reference.hpp"

#include "reactions.hpp"

void visitors::visitor_reference::visit(animals::ape& ape)
{
	reactions::react_to(ape);
}

void visitors::visitor_reference::visit(animals::bat& bat)
{
	reactions::react_to(bat);
}

void visitors::visitor_reference::visit(animals::cat& cat)
{
	reactions::react_to(cat);
}

void visitors::visitor_reference::visit(animals::dog& dog)
{
	reactions::react_to(dog);
}

void visitors::visitor_reference::visit(animals::elk& elk)
{
	reactions::react_to(elk);
}
