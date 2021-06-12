#include "testik.hpp"

#include <iostream>

N::B::B(M)
{
	std::cout << "B(M)\n";
}

N::M::M(D)
{
	std::cout << "M(D)\n";
}

void N::f(B)
{}
