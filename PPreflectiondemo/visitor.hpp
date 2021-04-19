#pragma once
#include "animals.hpp"

struct dynamic_reaction_visitor
{
	void react_to(const animals::animal& animal);
};
