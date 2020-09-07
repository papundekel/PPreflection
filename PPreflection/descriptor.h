#pragma once
#include <string_view>
#include <utility>
#include "simple_ostream.h"
#include "cref_t.h"
#include "pointer_view.h"

class descriptor
{
public:
	template <PP::view View>
	static constexpr decltype(&std::declval<PP::view_base_t<View>>()) get_descriptor(std::string_view name, View&& descriptors) noexcept
	{
		for (auto&& d : std::forward<View>(descriptors))
			if (d.has_name(name))
				return &d;

		return nullptr;
	}

	constexpr virtual void print_name(simple_ostream& out) const noexcept = 0;
	constexpr virtual bool has_name(std::string_view name) const noexcept = 0;

	template <typename T>
	static constexpr std::string_view reflect_name() noexcept;
};

std::ostream& operator<<(std::ostream& out, const descriptor& d);
