#pragma once
#include "PP/add_pointer.hpp"
#include "PP/remove_extent.hpp"

#include "../complete_object_type.h"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_array_type : public Base
	{
		static_assert(PP::concepts::array<T>);

		static constexpr auto element_type = PP::remove_extent(PP::type<T>);

	public:
		constexpr cv_type<complete_object_type> remove_extent() const noexcept
		{
			return type::reflect_cv(element_type);
		}

		constexpr convertor_object array_to_pointer_conversion() const noexcept override final
		{
			return create_convertor_object_to_value(PP::type<T>);
		}

		constexpr const pointer_type& get_pointer_to_element() const noexcept override final
		{
			return type::reflect(PP::add_pointer(element_type));
		}
	};
}
