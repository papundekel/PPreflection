#pragma once

namespace N
{
	class C
	{
		int x;

	public:
		C();
		explicit C(int a);
		~C();

		int f(int a) const;

		static int g(int a);

		operator int() const;
	};
}
