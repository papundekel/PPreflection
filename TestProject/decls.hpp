#pragma once

struct loud
{
	int id;

	loud(int id);
	loud(const loud& copy);
	loud(loud&& other);
	~loud();
};

int f(float);
float f(int);

void print_loud(const loud&);

class B
{

};

class D : B
{

};
