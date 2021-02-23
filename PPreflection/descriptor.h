#pragma once
#include <iosfwd>

#include "simple_ostream.hpp"
#include "string_view.hpp"
#include "type_t.hpp"
#include "view.hpp"

namespace PPreflection
{
	using namespace PP::literals;

	class descriptor
	{
		constexpr virtual void print_name_before_parent(PP::simple_ostream& out) const noexcept = 0;
		constexpr virtual void print_name_after_parent(PP::simple_ostream& out) const noexcept = 0;

	public:
		constexpr virtual const descriptor& get_parent() const noexcept = 0;

		constexpr void print_name(PP::simple_ostream& out) const noexcept
		{
			print_name_before_parent(out);
			const descriptor& parent = get_parent();
			auto parent_address = &parent;
			auto t = this;
			if (parent_address != t)
			{
				parent.print_name(out);
				out.write("::");
			}
			print_name_after_parent(out);
		}
		constexpr virtual bool has_name(PP::string_view name) const noexcept = 0;

		static constexpr PP::string_view reflect_name(PP::concepts::type auto t) noexcept;

		static constexpr auto get_descriptor(PP::string_view name, PP::concepts::view auto&& descriptors) noexcept
			-> decltype(&declval(PP::view_base(descriptors)))
		{
			for (auto&& d : PP_FORWARD(descriptors))
				if (d.has_name(name))
					return &d;

			return nullptr;
		}
	};

	std::ostream& operator<<(std::ostream& out, const descriptor& d);
}
