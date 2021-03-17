#include "C.hpp"

N::C::C()
	: C(0)
{}

N::C::C(int a)
	: x(a)
{}

N::C::~C()
{}

int N::C::f(int a) const
{
	return x + a;
}

int N::C::g(int a)
{
	return a * 2;
}

N::C::operator int() const
{
	return x * 5;
}
