#pragma once
#include <type_traits>
#include "basic_user_defined_type.hpp"
#include "../class_type.h"
#include "../../functions/constructor.h"
#include "../../functions/member_function.h"
#include "../../functions/static_member_function.h"
#include "../../reflect.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_class_type : public basic_user_defined_type<T, Base>
	{
		static constexpr auto static_member_functions =
			reflect_many(reflect(PP::type_v<reflection::static_member_functions<T>>), PP::type_v<const static_member_function::overloaded&>);
		static constexpr auto member_functions =
			reflect_many(reflect(PP::type_v<reflection::member_functions<T>>), PP::type_v<const member_function::overloaded&>);
		static constexpr auto nested_classes =
			reflect_many(reflect(PP::type_v<reflection::nested_classes<T>>), PP::type_v<const user_defined_type&>);

	public:
		static_assert(std::is_class_v<T> || std::is_union_v<T>);
		static_assert(std::is_base_of_v<class_type, Base>);

		void destroy(void* ptr) const noexcept override final
		{
			if constexpr (std::is_destructible_v<T>)
				std::destroy_at(reinterpret_cast<T*>(ptr));
			else
				std::terminate();
		}

		constexpr const overloaded_constructor& get_constructors() const noexcept override final
		{
			return reflect(PP::type_v<reflection::constructors<T>>);
		}
		constexpr PP::any_view<const member_function::overloaded&> get_member_functions() const noexcept override final
		{
			return member_functions;
		}
		constexpr PP::any_view<const static_member_function::overloaded&> get_static_member_functions() const noexcept override final
		{
			return static_member_functions;
		}

		constexpr PP::any_view<const user_defined_type&> get_nested_classes() const noexcept override final
		{
			return nested_classes;
		}
	};
}
