#pragma once
#include "basic_overloaded_function.h"
#include "overloaded_member_like_function.h"
#include "member_like_function.h"

template <typename ID, typename Class, typename Functions>
class basic_overloaded_static_member_function : public basic_overloaded_function<ID, overloaded_member_like_function<member_like_function>>
{
public:
	constexpr simple_range<const cref_t<member_like_function>> get_overloads() const noexcept override final;

	constexpr const type& get_enclosing_class() const noexcept override final;
};
