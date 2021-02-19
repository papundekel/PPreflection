#pragma once
#include "../descriptor.h"
#include "string_view.hpp"

namespace PPreflection
{
	namespace detail
	{
		template <typename Base>
		class dynamic_named_descriptor : public Base
		{
			static_assert(PP::derived_from<Base, descriptor>);

			std::string name;

		public:
			constexpr dynamic_named_descriptor(PP::string_view name, auto&&... args) noexcept
				: Base(PP_FORWARD(args)...)
				, name_(name)
			{}

			constexpr bool has_name(PP::string_view name) const noexcept override final
			{
				return view_equal(this->name, name);
			}
			constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
			{
				out.write(name);
			}
			constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final
			{}
		};
	}
}
