#pragma once
#include "functions/conversion_function.h"

namespace PPreflection::detail
{
class initialization;

class conversion_function_olr : public conversion_function
{
	friend initialization;

	const conversion_function& inner_function;
	const class_type& class_;

public:
	constexpr conversion_function_olr(const conversion_function& inner_function,
	                                  const class_type& class_)
		: inner_function(inner_function)
		, class_(class_)
	{}

private:
	constexpr bool is_explicit() const noexcept override final
	{
		return inner_function.is_explicit();
	}

	constexpr const class_type& get_parent() const noexcept override final
	{
		return inner_function.get_parent();
	}

	dynamic_variable invoke_unsafe(
		dynamic_reference caller) const override final
	{
		return inner_function.invoke_unsafe(caller);
	}

	constexpr const function_type& get_function_type()
		const noexcept override final
	{
		return inner_function.get_function_type();
	}
};
}
