#include <iostream>
#include "string_ostream.hpp"

int main()
{
	string_ostream so;

	simple_ostream& stream = so;

	stream.write(0);
	stream.write("\ncool\n");

	stream.write_to_ostream(std::cout);

	std::cout.flush();
	return 0;
}
