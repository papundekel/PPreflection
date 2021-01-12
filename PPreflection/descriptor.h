#pragma once
#include <string_view>
#include <utility>
#include "simple_ostream.hpp"
#include "view.hpp"
#include "type_t.hpp"

class descriptor
{
	constexpr virtual const descriptor* get_parent_implementation() const noexcept = 0;

	constexpr virtual void print_name_before_parent(PP::simple_ostream& out) const noexcept = 0;
	constexpr virtual void print_name_after_parent(PP::simple_ostream& out) const noexcept = 0;

public:
	constexpr void print_name(PP::simple_ostream& out) const noexcept
	{
		print_name_before_parent(out);
		if (const descriptor* parent = get_parent_implementation(); parent)
		{
			parent->print_name(out);
			out.write("::");
		}
		print_name_after_parent(out);
	}
	constexpr virtual bool has_name(std::string_view name) const noexcept = 0;

	template <typename T>
	static constexpr std::string_view reflect_name(PP::type_t<T>) noexcept;

	static constexpr auto get_descriptor(std::string_view name, PP::concepts::view auto&& descriptors) noexcept
		-> decltype(&declval(PP::view_base(descriptors)))
	{
		for (auto&& d : PP_FORWARD(descriptors))
			if (d.has_name(name))
				return &d;

		return nullptr;
	}
};

std::ostream& operator<<(std::ostream& out, const descriptor& d);
