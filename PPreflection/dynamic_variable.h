#pragma oncec
#include <variant>
#include "dynamic_object.h"
#include "dynamic_reference.h"
#include "../PP/PP/overloaded.hpp"

class dynamic_variable
{
	std::variant<dynamic_reference, dynamic_object> dynamic;

	inline explicit dynamic_variable(dynamic_reference r)
		: dynamic(std::move(r))
	{}
	inline explicit dynamic_variable(dynamic_object o)
		: dynamic(std::move(o))
	{}

public:
	template <typename F>
	static inline dynamic_variable create(F&& f)
	{
		using R = decltype(std::forward<F>(f)());

		if constexpr (std::is_void_v<R>)
		{
			std::forward<F>(f)();
			return dynamic_variable(dynamic_object::create_void());
		}
		else if constexpr (std::is_reference_v<R>)
			return dynamic_variable(dynamic_reference(std::forward<F>(f)()));
		else
			return dynamic_variable(dynamic_object(std::forward<F>(f)()));
	}
	inline explicit operator bool() const noexcept
	{
		return std::visit(PP::overloaded{ [](const dynamic_reference&) { return true; },
			[](const dynamic_object& o)
			{
				return (bool)o;
			} }, dynamic);
	}
	static inline dynamic_variable create_invalid() noexcept
	{
		return dynamic_variable(dynamic_object::create_invalid());
	}
};
