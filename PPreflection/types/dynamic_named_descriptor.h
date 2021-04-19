#pragma once
#include "PP/small_optimized_vector.hpp"
#include "PP/string_view.hpp"

#include "../descriptor.h"

namespace PPreflection
{
	namespace detail
	{
		template <typename Base>
		class dynamic_named_descriptor : public Base
		{
			static_assert(PP::concepts::derived_from<Base, descriptor>);

			PP::small_optimized_vector<char, 32> name;

		public:
			constexpr dynamic_named_descriptor(PP::string_view name, auto&&... args) noexcept
				: Base(PP_FORWARD(args)...)
				, name()
			{
				for (char c : name)
					this->name.push_back(c);
			}

			constexpr PP::string_view get_name() const noexcept override final
			{
				return this->name;
			}
		};
	}
}
