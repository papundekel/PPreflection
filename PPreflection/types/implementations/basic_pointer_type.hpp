#pragma once
#include "../pointer_type.h"
#include "basic_non_array_object_type.hpp"
#include "concepts/pointer.hpp"
#include "remove_pointer.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_pointer_type final : public basic_cv_qualifiable_type<T, basic_complete_object_type<T, pointer_type>>
	{
		static_assert(PP::concepts::pointer<T>);

		constexpr const pointable_type& remove_pointer() const noexcept override final
		{
			return this->reflect | PP::remove_pointer <<= PP::type<T>;
		}
	};
}
