#pragma once
#include "basic_overloaded_function.h"
#include "overloaded_member_function.h"

namespace detail
{
	template <typename ID, typename Functions, typename Base>
	class basic_overloaded_member_function_base : public basic_overloaded_function<ID, Base>
	{
		using overload_base = Base::overload_type;

	public:
		constexpr pointer_view<const cref_t<overload_base>> get_overloads() const noexcept override final
		{
			return reflect_many<Functions, overload_base>();
		}

		constexpr const type& get_enclosing_class() const noexcept override final
		{
			return get_overloads().begin()->get().get_enclosing_class();
		}
	};
}
