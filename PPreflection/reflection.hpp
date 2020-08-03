#pragma once
#include <memory>
#include "overload_cast.hpp"
#include "simple_range.hpp"
#include "rvalue_reference_wrapper.hpp"
#include "dynamic_ptr.hpp"
#include "type.hpp"
#include "descriptor.hpp"
#include "function.hpp"

class namespace_t : public descriptor
{
	const char* name;
	simple_range<const function> functions;

public:
	constexpr namespace_t(const char* name, simple_range<const function> functions) noexcept
		: name(name)
		, functions(functions)
	{}

	constexpr void print_name(simple_ostream& out) const noexcept final
	{
		out.write(name);
	}

	constexpr simple_range<const function> get_functions() const noexcept
	{
		return functions;
	}
};

template <std::size_t function_count>
class namespace_t_owning : public namespace_t
{
	std::array<function, function_count> functions;

public:
	constexpr namespace_t_owning(const char* name, const std::array<function, function_count>& functions) noexcept
		: namespace_t(name, this->functions)
		, functions(functions)
	{
		std::transform(functions.begin(), functions.end(), this->functions.begin(),
			[this](const function& x)
			{
				return x.set_parent(this);
			});
	}
};



long long f(int, int&);
int f(int);

constexpr inline namespace_t_owning global_namespace("global'", std::array<function, 1>
{
	function("f", function::helper<long long, int, int&>::help<f>)
});

constexpr inline const function& f_ = global_namespace.get_functions()[0];

template <auto f>
constexpr inline int get_f {};

template <>
constexpr inline const function& get_f<overload_caster<int, int&>::cast(f)> = f_;
