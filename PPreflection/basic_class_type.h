#pragma once
#include <string_view>
#include "basic_type.h"

namespace detail
{
	template <typename Namespace, typename T, typename MemberFunctions, typename Bases>
	class basic_class_type : public basic_type<T>
	{
	public:
		constexpr simple_range<const cref_t<type>> get_direct_bases() const noexcept override final;
		constexpr virtual const namespace_t* get_namespace() const noexcept override final;

		constexpr simple_range<const cref_t<overloaded_member_function>> get_member_functions() const noexcept override final;
	};
}
