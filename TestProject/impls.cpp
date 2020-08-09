#include "decls.hpp"
#include <iostream>

loud::loud(int id) : id(id) {}
loud::loud(const loud& copy){}
loud::loud(loud&& other){}
loud::~loud(){}

int f(float x)
{
	return x;
}
float f(int x)
{
	return x;
}

void print_loud(const loud& x)
{
	std::cout << x.id << '\n';
}
