#include "animals.hpp"

const char*
animals::ape::name() const noexcept
{
	return "ape";
}

const char*
animals::bat::name() const noexcept
{
	return "bat";
}

const char*
animals::cat::name() const noexcept
{
	return "cat";
}

const char*
animals::dog::name() const noexcept
{
	return "dog";
}

const char*
animals::elk::name() const noexcept
{
	return "elk";
}

void
animals::ape::accept(visitors::animal_visitor& visitor)
{
	visitor.visit(*this);
}

void
animals::bat::accept(visitors::animal_visitor& visitor)
{
	visitor.visit(*this);
}

void
animals::cat::accept(visitors::animal_visitor& visitor)
{
	visitor.visit(*this);
}

void
animals::dog::accept(visitors::animal_visitor& visitor)
{
	visitor.visit(*this);
}

void
animals::elk::accept(visitors::animal_visitor& visitor)
{
	visitor.visit(*this);
}
