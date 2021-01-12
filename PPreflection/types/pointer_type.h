#pragma once
#include "non_array_object_type.h"
#include "non_user_defined_type.h"

class pointer_type : public detail::non_user_defined_type<non_array_object_type>
{
public:
	constexpr bool has_name(std::string_view name) const noexcept override final
	{
		return false;
	}
	constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
	{
		remove_pointer().print_name_prefix(out);
		out.write("(*");
	}
	constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final
	{
		out.write(")");
		remove_pointer().print_name_suffix(out);
	}

	constexpr std::size_t alignment() const noexcept
	{
		return alignof(void*);
	}
	constexpr std::size_t size() const noexcept
	{
		return sizeof(void*);
	}
	constexpr void destroy(void* ptr) const noexcept
	{}

	constexpr virtual const pointable_type& remove_pointer() const noexcept = 0;
};
