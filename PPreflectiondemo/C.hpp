#pragma once

namespace N
{
	struct B
	{

	};

	struct S : public B
	{
		explicit S(const S&) = delete;

		void f() const&;

		static int g(double);
		static double g(int);
	};
}
