#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

#include "PP/size_t.hpp"

#include "animals.hpp"
#include "reactions.hpp"
#include "visitor.hpp"

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

int main()
{
	PP::size_t count;
	std::cin >> count;

	auto zoo = generate_zoo(count);

	dynamic_reaction_visitor visitor;

	auto time_start = std::chrono::system_clock::now();
	
	for (const auto& animal_ptr : zoo)
	{
		visitor.react_to(*animal_ptr);
	}

	auto time_end = std::chrono::system_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count() << '\n';

	std::cout.flush();
	return 0;
}
