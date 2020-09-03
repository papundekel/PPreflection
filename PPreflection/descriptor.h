#pragma once
#include <string_view>
#include "simple_ostream.h"
#include "cref_t.h"
#include "pointer_view.h"

class descriptor
{
public:
	template <typename Descriptor>
	static constexpr const Descriptor* get_descriptor(std::string_view name, pointer_view<const cref_t<Descriptor>> descriptors) noexcept;

	constexpr virtual void print_name(simple_ostream& out) const noexcept = 0;
	constexpr virtual bool has_name(std::string_view name) const noexcept = 0;

	template <typename T>
	static constexpr std::string_view reflect_name() noexcept;
};

std::ostream& operator<<(std::ostream& out, const descriptor& d);
