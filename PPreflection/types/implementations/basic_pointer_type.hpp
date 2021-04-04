#pragma once
#include "PP/add_pointer.hpp"
#include "PP/concepts/function.hpp"
#include "PP/concepts/pointer.hpp"
#include "PP/remove_pointer.hpp"
#include "PP/to_void_ptr.hpp"

#include "../pointer_type.h"
#include "basic_complete_object_type.hpp"
#include "basic_pointer_base_type.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_pointer_type final : public basic_pointer_base_type<T, basic_complete_object_type<T, pointer_type>>
	{
		static_assert(PP::concepts::pointer<T>);

		static constexpr auto pointed_to_type = PP::remove_pointer(PP::type<T>);

		constexpr cv_type<pointable_type> remove_pointer() const noexcept override final
		{
			return type::reflect_cv(pointed_to_type);
		}

		constexpr convertor_object void_conversion() const noexcept override final
		{
			if constexpr (!PP::is_function(pointed_to_type))
				return create_convertor_object(PP::type<T>, PP::value<PP::to_void_ptr>);
			else
				return [](dynamic_reference) -> dynamic_object { throw 0; };
		}
	};
}
