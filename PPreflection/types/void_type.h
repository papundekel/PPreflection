#pragma once
#include "array.hpp"
#include "pointable_type.h"
#include "cv_qualifier.hpp"
#include "add_cv.hpp"
#include "cv_qualifiable_type.h"
#include "non_user_defined_type.h"

class void_type : public detail::non_user_defined_type<detail::cv_qualifiable_type<pointable_type>>
{
	static const std::array<const pointer_type*, 4> types;
	static const std::array<std::string_view, 4> names;

public:
	constexpr const pointer_type& make_pointer() const noexcept
	{
		return *types[(std::size_t)get_cv_qualifier()];
	}

	constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
	{
		out.write(names[(std::size_t)get_cv_qualifier()]);
	}
	constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final
	{}
	constexpr bool has_name(std::string_view name) const noexcept override final
	{
		return names[(std::size_t)get_cv_qualifier()] == name;
	}
};

const std::array<const pointer_type*, 4> void_type::types =
{
	&type::reflect(PP::type_v<void*>),
	&type::reflect(PP::type_v<const void*>),
	&type::reflect(PP::type_v<volatile void*>),
	&type::reflect(PP::type_v<const volatile void*>),
};

const std::array<std::string_view, 4> void_type::names =
{
	"void",
	"void const",
	"void volatile",
	"void const volatile",
};
