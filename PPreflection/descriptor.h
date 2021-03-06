#pragma once
#include <iosfwd>

#include "PP/get_type.hpp"
#include "PP/simple_ostream.hpp"
#include "PP/simple_vector.hpp"
#include "PP/string_view.hpp"
#include "PP/view.hpp"

#include "parent_descriptor_reference.h"

namespace PPreflection
{
	using namespace PP::literals;

	class descriptor
	{
	public:
		constexpr virtual void print_name_before_parent(PP::simple_ostream& out) const noexcept = 0;
		constexpr virtual void print_name_after_parent(PP::simple_ostream& out) const noexcept = 0;

		constexpr virtual parent_descriptor_reference get_parent(void* = nullptr) const noexcept = 0;

		constexpr void print_name(PP::simple_ostream& out) const noexcept;
		constexpr virtual bool has_name(PP::string_view name) const noexcept = 0;

		static constexpr PP::string_view reflect_name(PP::concepts::type auto t) noexcept;

		static constexpr auto get_descriptor(PP::string_view name, PP::concepts::view auto&& descriptors) noexcept
			-> decltype(&PP::declval(PP::view_base(PP_DECLTYPE(descriptors))))
		{
			for (auto& d : PP_FORWARD(descriptors))
				if (d.has_name(name))
					return &d;

			return nullptr;
		}
	};

	std::ostream& operator<<(std::ostream& out, const descriptor& d);
}
