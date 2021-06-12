#pragma once
#include "S.hpp"

namespace N
{
	struct M;

	struct B
	{
		long long x;

		B() = default;
		B(M);
	};

	struct D;

	struct M
		: B
	{
		long long y;

		M() = default;
		M(D);
	};

	struct D
		: M
	{
		long long z;

		D() = default;
		D(const D&) = default;
	};

	void f(B b);

	void g();
}
