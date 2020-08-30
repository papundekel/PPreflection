#pragma once
#include "overloaded_member_like_function.h"
#include "member_like_function.h"
#include "basic_overloaded_function.h"

template <typename Class, typename Constructors>
class basic_overloaded_constructor : public basic_overloaded_function<Class, overloaded_member_like_function<member_like_function>>
{
public:
	constexpr simple_range<const cref_t<member_like_function>> get_overloads() const noexcept override final;

	constexpr const type& get_enclosing_class() const noexcept override final;
};
