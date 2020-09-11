#pragma once
#include "basic_overloaded_function.h"
#include "../namespace_function.h"

namespace detail
{
	template <typename ID, typename Namespace, typename Functions>
	class basic_overloaded_namespace_function final : public basic_overloaded_function<ID, Functions, namespace_function>
	{
	public:
		constexpr PP::any_view<const namespace_function&> get_namespace_overloads() const noexcept override final
		{
			return reflect_many<Functions, const namespace_function&>();
		}

		constexpr const namespace_t& get_parent() const noexcept override final
		{
			return reflect<Namespace, namespace_t>();
		}
	};
}
