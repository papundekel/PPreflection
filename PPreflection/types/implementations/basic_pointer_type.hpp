#pragma once
#include "PP/add_pointer.hpp"
#include "PP/concepts/function.hpp"
#include "PP/concepts/pointer.hpp"
#include "PP/remove_pointer.hpp"

#include "../pointer_type.h"
#include "basic_non_array_object_type.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_pointer_type final : public basic_complete_object_type<T, pointer_type>
	{
		static_assert(PP::concepts::pointer<T>);

		static constexpr auto pointed_to_type = PP::remove_pointer(PP::type<T>);

		constexpr cv_type<pointable_type> remove_pointer() const noexcept override final
		{
			return type::reflect_cv(pointed_to_type);
		}

		constexpr convertor_object bool_conversion() const noexcept override final
		{
			return create_convertor_object(PP::type<T>, PP::value<[]
				(auto* p) -> bool
				{
					return p;
				}>);
		}

		constexpr convertor_object void_conversion() const noexcept override final
		{
			return create_convertor_object(PP::type<T>, PP::value<[]
				(auto* p)
				{
					return PP::copy_cv(pointed_to_type, PP::type_void)(p);
				}>);
		}
	};
}
