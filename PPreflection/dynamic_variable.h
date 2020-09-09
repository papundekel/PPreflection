#pragma once
#include <variant>
#include "dynamic_object.h"
#include "dynamic_reference.h"

class dynamic_variable
{
	std::variant<dynamic_reference, dynamic_object> dynamic;

	explicit constexpr dynamic_variable(dynamic_reference r)
		: dynamic(std::move(r))
	{}
	explicit constexpr dynamic_variable(dynamic_object o)
		: dynamic(std::move(o))
	{}

public:
	template <typename F>
	constexpr dynamic_variable create(F&& f)
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
			return dynamic_variable(dynamic_object(reflect<R, object_type>(),
				[&f](void* ptr)
				{
					new (ptr) R(std::forward<F>(f)());
				}));
	}
};
