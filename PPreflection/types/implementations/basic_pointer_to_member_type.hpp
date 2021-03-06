#pragma once
#include "PP/concepts/pointer_to_member.hpp"
#include "PP/pointer_to_member_info.hpp"

#include "../pointer_to_member_type.h"
#include "basic_non_array_object_type.hpp"
namespace PPreflection::detail
{
	template <typename T>
	class basic_pointer_to_member_type final : public basic_non_array_object_type<T, pointer_to_member_type>
	{
		static_assert(PP::concepts::pointer_to_member<T>);

		static constexpr auto info = PP::pointer_to_member_info(PP::type<T>);

		constexpr const class_type& get_class_type() const noexcept override final
		{
			return type::reflect(info.class_type);
		}
		constexpr cv_type<referencable_type> get_member_type() const noexcept override final
		{
			return type::reflect_cv(info.member_type);
		}
	};
}
