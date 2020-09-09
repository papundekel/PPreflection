#pragma once
#include <string_view>
#include <utility>
#include "simple_ostream.h"
#include "cref_t.h"
#include "pointer_view.h"

class descriptor
{
	constexpr virtual const descriptor* get_parent_implementation() const noexcept = 0;

	constexpr virtual void print_name_before_parent(simple_ostream& out) const noexcept = 0;
	constexpr virtual void print_name_after_parent(simple_ostream& out) const noexcept = 0;

public:
	template <PP::view View>
	static constexpr decltype(&std::declval<PP::view_base_t<View>>()) get_descriptor(std::string_view name, View&& descriptors) noexcept
	{
		for (auto&& d : std::forward<View>(descriptors))
			if (d.has_name(name))
				return &d;

		return nullptr;
	}
	constexpr void print_name(simple_ostream& out) const noexcept
	{
		print_name_before_parent(out);
		const descriptor* parent = this;
		while (true)
		{
			parent = parent->get_parent_implementation();
			if (!parent)
				break;
			parent->print_name(out);
			out.write("::");
		}
		print_name_after_parent(out);
	}
	constexpr virtual bool has_name(std::string_view name) const noexcept = 0;

	template <typename T>
	static constexpr std::string_view reflect_name() noexcept;
};

std::ostream& operator<<(std::ostream& out, const descriptor& d);
