#pragma once
#include "overloaded_member_like_function.h"
#include "member_like_function.h"
#include "basic_overloaded_function.h"
#include "constructor_info.h"
#include "map_pack.h"

namespace detail
{
	template <typename Class, typename Constructors>
	class basic_overloaded_constructor : public basic_overloaded_function<Class, overloaded_member_like_function<member_like_function>>
	{
	public:
		constexpr pointer_view<const cref_t<member_like_function>> get_overloads() const noexcept override final
		{
			return reflect_many<map_pack_types<make_full_info<Class>::template make, Constructors>, member_like_function>();
		}

		constexpr const type& get_enclosing_class() const noexcept override final
		{
			return reflect<Class, type>();
		}
	};
}
