#pragma once
#include "../types/class_type.h"
#include "function.h"

namespace PPreflection
{
	namespace detail
	{
		class overloaded_maybe_static_member_function : public function::overloaded
		{
			constexpr parent_descriptor_reference_strong get_parent(int) const noexcept override final
			{
				return get_parent();
			}

		public:
			constexpr virtual const class_type& get_parent() const noexcept = 0;
		};

		class maybe_static_member_function : public function
		{
			constexpr parent_descriptor_reference_strong get_parent(int) const noexcept override final
			{
				return get_parent();
			}

		public:
			using overloaded = overloaded_maybe_static_member_function;

			constexpr const overloaded& get_overloaded_function() const noexcept override = 0;

			constexpr virtual const class_type& get_parent() const noexcept
			{
				return get_overloaded_function().get_parent();
			}
		};
	}
}
