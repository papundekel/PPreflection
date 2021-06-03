#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

#include "PP/size_t.hpp"

#include "animals.hpp"
#include "reactions.hpp"

#include "visitor_reference.hpp"
#include "visitor_reflection.hpp"

auto generate_zoo(PP::size_t count)
{
	using namespace PP::literals;

	std::vector<std::unique_ptr<animals::animal>> zoo;

	zoo.reserve(count);

	std::srand(std::time(nullptr));

	for (auto i = 0_z; i != count; ++i)
	{
		std::unique_ptr<animals::animal> ptr;

		auto x = std::rand() % 5;

		switch (x)
		{
			case 0:
				ptr = std::make_unique<animals::ape>();
				break;
			case 1:
				ptr = std::make_unique<animals::bat>();
				break;
			case 2:
				ptr = std::make_unique<animals::cat>();
				break;
			case 3:
				ptr = std::make_unique<animals::dog>();
				break;
			case 4:
				ptr = std::make_unique<animals::elk>();
				break;
			default:
				break;
		}

		zoo.push_back(std::move(ptr));
	}

	return zoo;
}

auto now()
{
	return std::chrono::system_clock::now();
}

using time_point = decltype(now());

void print_duration(time_point time)
{
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(now() -
																	   time)
					 .count()
			  << '\n';
}

int main()
{
	PP::size_t count;
	std::cin >> count;

	auto zoo = generate_zoo(count);

	visitors::visitor_reference v_reference;

	auto time = now();

	for (const auto& animal_ptr : zoo)
	{
		animal_ptr->accept(v_reference);
	}

	print_duration(time);

	std::cout << animals::value << '\n';
	animals::value = -1;

	visitors::visitor_reflection v_reflection;

	time = now();

	for (const auto& animal_ptr : zoo)
	{
		v_reflection.react_to(*animal_ptr);
	}

	print_duration(time);

	std::cout << animals::value << '\n';

	std::cout.flush();
	return 0;
}
