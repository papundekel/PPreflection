#pragma once
#include "basic_overloaded_member_function.h"
#include "conversion_function_info.h"

class overloaded_conversion_function;

namespace detail
{
	template <typename ID, typename Functions>
	using basic_overloaded_conversion_function_helper = basic_overloaded_member_function_base
		< empty_id
		, map_pack_types<make_conversion_function<typename ID::Class, typename ID::Result>::template make, Functions>
		, overloaded_conversion_function>;

	template <typename ID, typename Functions>
	class basic_overloaded_conversion_function final : public basic_overloaded_conversion_function_helper<ID, Functions>
	{
		using MappedFunctions = basic_overloaded_conversion_function_helper<ID, Functions>::Functions;

	public:
		constexpr void print_name(simple_ostream& out) const noexcept override final
		{
			out.write("operator ");
			out.write(descriptor::reflect_name<typename ID::Result>());
		}
		constexpr bool has_name(std::string_view name) const noexcept override final
		{
			return name.starts_with("operator ") && name.substr(9) == descriptor::reflect_name<typename ID::Result>();
		}
		constexpr pointer_view<const cref_t<conversion_function>> get_conversion_overloads() const noexcept override final
		{
			return reflect_many<MappedFunctions, conversion_function>();
		}
	};
}
