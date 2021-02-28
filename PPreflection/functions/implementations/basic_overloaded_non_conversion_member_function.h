#pragma once
#include "basic_overloaded_member_function.h"
#include "basic_overloaded_named_function.h"

namespace PPreflection::detail
{
	template <typename ID>
	class basic_overloaded_non_conversion_member_function final
		: public basic_overloaded_named_function<ID, basic_overloaded_member_function<ID, non_conversion_member_function>>
	{
		constexpr const class_type& get_parent() const noexcept override final
		{
			for (const member_function& mf : this->get_overloads())
				return mf.get_parent();

			std::terminate();
		}
	};
}
