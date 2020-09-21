#pragma once
#include "basic_user_defined_type.hpp"
#include "../class_type.h"
#include "../functions/constructor.h"
#include "../functions/member_function.h"
#include "../functions/static_member_function.h"
#include "../../reflect.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_class_type : public basic_user_defined_type<T, Base>
	{
		static_assert(std::is_class_v<T> || std::is_union_v<T>);
		static_assert(std::is_base_of_v<class_type, Base>);

		constexpr const overloaded_constructor& get_constructors() const noexcept override final
		{
			return ::reflect<overloaded_constructor_info<T>, const overloaded_constructor&>();
		}
		constexpr PP::any_view<const member_function&> get_member_functions() const noexcept override final
		{
			return ::reflect<member_functions<T>, const member_function&>();
		}
		constexpr PP::any_view<const static_member_function&> get_static_member_functions() const noexcept override final
		{
			return ::reflect<static_member_functions<T>, const static_member_function&>();
		}
		constexpr PP::any_view<const class_type&> get_nested_classes() const noexcept override final
		{
			return ::reflect<nested_classes<T>, const class_type&>();
		}
	};
}
