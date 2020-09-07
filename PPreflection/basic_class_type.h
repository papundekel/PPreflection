#pragma once
#include <string_view>
#include "basic_type.h"
#include "reflect.h"

namespace detail
{
	template <typename Namespace, typename T, typename MemberFunctions, typename Bases>
	class basic_class_type : public basic_type<T>
	{
	public:
		constexpr any_view<const type&> get_direct_bases() const noexcept override final
		{
			return reflect_many<Bases, type>();
		}
		constexpr virtual const namespace_t* get_namespace() const noexcept override final
		{
			return &reflect<Namespace, namespace_t>();
		}

		constexpr any_view<const overloaded_member_function&> get_member_functions() const noexcept override final
		{
			return reflect_many<MemberFunctions, overloaded_member_function>();
		}
		constexpr const overloaded_constructor* get_constructors() const noexcept override final
		{
			return &reflect<constructor_wrap<T>, overloaded_constructor>();
		}
	};
}
