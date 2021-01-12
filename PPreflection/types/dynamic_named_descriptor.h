#pragma once
#include <string_view>
#include "../descriptor.h"

namespace detail
{
	template <typename Base>
	class dynamic_named_descriptor : public Base
	{
		static_assert(std::is_base_of_v<descriptor, Base>);

		std::string name_;

	public:
		constexpr dynamic_named_descriptor(std::string_view name, auto&&... b) noexcept
			: Base(std::forward<decltype(b)>(b)...)
			, name_(name)
		{}

		constexpr bool has_name(std::string_view name) const noexcept override final
		{
			return name_ == name;
		}
		constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
		{
			out.write(name_);
		}
		constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final
		{}
	};
}
