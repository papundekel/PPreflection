#pragma once
#include "PP/get_type.hpp"
#include "PP/get_value.hpp"

namespace PPreflection
{
	class dynamic_reference;
	class dynamic_variable;
	class dynamic_object;

	using convertor = dynamic_variable(*)(dynamic_reference);
	using convertor_object = dynamic_object(*)(dynamic_reference);

	constexpr convertor create_convertor(PP::concepts::type auto t, PP::concepts::value auto f) noexcept;
	constexpr convertor_object create_convertor_object(PP::concepts::type auto t, PP::concepts::value auto f) noexcept;

	namespace detail
	{
		constexpr inline auto to_value_functor_value = PP::value<[]
			(const auto& x)
			{
				return x;
			}>;
	}

	constexpr convertor create_convertor_to_value(PP::concepts::type auto t) noexcept
	{
		return create_convertor(t, detail::to_value_functor_value);
	}
	constexpr convertor_object create_convertor_object_to_value(PP::concepts::type auto t) noexcept
	{
		return create_convertor_object(t, detail::to_value_functor_value);
	}
}
