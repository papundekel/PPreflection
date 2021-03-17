#pragma once

namespace G
{
	enum E
	{
		a = 5,
	};

	namespace A{}
	namespace B{}
	namespace C{}
	namespace D{}
}

namespace M
{
	int f(int);
}
namespace M
{
	int f(int, int);
	int f(int, int, int);
}
