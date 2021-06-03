#pragma once
#include "PP/size_t.hpp"

#include "object_type.h"

namespace PPreflection
{
	class known_bound_array_type;
	class non_array_object_type;

	class complete_object_type : public object_type
	{
	public:
		constexpr PP::variant<const unknown_bound_array_type&,
							  const complete_object_type&>
			cast_down(
				PP::overload_tag<object_type>) const noexcept override final
		{
			return { PP::placeholder, *this };
		}
		constexpr virtual PP::variant<const known_bound_array_type&,
									  const non_array_object_type&>
			cast_down(
				PP::overload_tag<complete_object_type> = {}) const noexcept = 0;

		constexpr virtual PP::size_t size() const noexcept = 0;
		constexpr virtual void destroy(void* ptr) const noexcept = 0;
	};
}
