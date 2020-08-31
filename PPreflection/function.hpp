#pragma once
#include <type_traits>
#include <vector>
#include "function.h"
#include "dynamic_object.h"
#include "type.h"
#include "get_value.h"
#include "conversion_function.h"
#include "dynamic_reference.h"

template <typename... Parameters>
constexpr typename function::invoke_helper_t<Parameters...>::x function::invoke_helper_t<Parameters...>::value_f() noexcept
{
	return {};
}
template <typename... Parameters>
template <typename F, std::size_t... I>
constexpr decltype(auto) function::invoke_helper_t<Parameters...>::x::helper(F&& f, const dynamic_reference* args, std::index_sequence<I...>) noexcept
{
	return std::forward<F>(f)(args[I].cast_unsafe<Parameters>()...);
}

template <typename... Parameters>
template <typename F>
constexpr decltype(auto) function::invoke_helper_t<Parameters...>::x::operator()(F&& f, const dynamic_reference* args) const noexcept
{
	return helper(std::forward<F>(f), args, std::index_sequence_for<Parameters...>{});
}

constexpr bool function::can_invoke(pointer_view<const dynamic_reference> args) const noexcept
{
	return type::can_initialize_arguments(
		parameter_types(),
		args | PP::transform([](const dynamic_reference& r) -> const type& { return r.get_type(); }));
}

constexpr dynamic_object function::invoke_unsafe(pointer_view<const dynamic_reference> args) const noexcept
{
	return dynamic_object(return_type(),
		[this, args](void* ptr)
		{
			/*pointer_view<const cref_t<type>> pt = parameter_types();

			int pc = pt.count();
			int ac = args.count();

			if (pt.count() != args.count())
				throw 0;

			std::vector<dynamic_object> temps;
			std::vector<dynamic_reference> converted_args;

			{
				auto p = pt.begin();
				for (auto a = args.begin(); a != args.end(); ++a, ++p)
				{
					const type& at = a->get_type();
					const type& pt = *p;

					if (auto parameter_ref_q = pt.get_ref_qualifier(); parameter_ref_q == ref_qualifier::lvalue)
					{
						if (at.L1(pt))
							converted_args.push_back(std::move(*a));
						else if (const conversion_function* conversion = at.L2(pt); conversion)
						{
							temps.push_back(conversion->invoke_unsafe(*a));
							converted_args.push_back(temps.back());
						}
						else
							throw 1;
					}
					else if (parameter_ref_q == ref_qualifier::rvalue)
					{

					}
					else
						converted_args.push_back(std::move(*a));
				}
			}*/

			invoke_implementation(ptr, args.begin());
		});
}

constexpr dynamic_object function::invoke(pointer_view<const dynamic_reference> args) const
{
	if (can_invoke(args))
		return invoke_unsafe(args);
	else
		throw 0;
}
