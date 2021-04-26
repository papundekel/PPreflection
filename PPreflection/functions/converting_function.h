#pragma once

namespace PPreflection
{
	class converting_function
	{
	public:
		virtual dynamic_variable invoke(dynamic_reference arg) const = 0;
	}
}
