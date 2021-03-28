#pragma once
#include "complete_object_type.h"
#include "dynamic_pointer_type.h"

namespace PPreflection
{
	template <typename Base>
	class dynamic_array_type : public Base
	{
		cv_type<complete_object_type> inner_type;
		dynamic_pointer_type element_pointer_type;

	public:
		constexpr explicit dynamic_array_type(cv_type<complete_object_type> inner_type) noexcept
			: inner_type(inner_type)
			, element_pointer_type(inner_type)
		{}

		constexpr const pointer_type& get_pointer_to_element() const noexcept override final
		{
			return element_pointer_type;
		}

		constexpr cv_type<complete_object_type> remove_extent() const noexcept override final
		{
			return inner_type;
		}

		constexpr convertor_object array_to_pointer_conversion() const noexcept override final
		{
			return nullptr;
		}
	};
}
