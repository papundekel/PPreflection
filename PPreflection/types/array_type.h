#pragma once
#include "../descriptor.h"
#include "cv_qualifier.hpp"
#include "non_user_defined_type.h"

class complete_object_type;

namespace detail
{
	template <typename Base>
	class array_type : public non_user_defined_type<Base>
	{
	public:
		constexpr virtual const complete_object_type& remove_extent() const noexcept = 0;
		constexpr PP::cv_qualifier get_cv_qualifier() const noexcept override final
		{
			return remove_extent().get_cv_qualifier();
		}
		constexpr std::size_t alignment() const noexcept override final
		{
			return remove_extent().alignment();
		}
	};
}
