#pragma once
#include <iosfwd>

#include "get_type.hpp"
#include "simple_ostream.hpp"
#include "string_view.hpp"
#include "view.hpp"

namespace PPreflection
{
	using namespace PP::literals;

	class descriptor
	{
	protected:
		constexpr virtual void print_name_before_parent(PP::simple_ostream& out) const noexcept = 0;
		constexpr virtual void print_name_after_parent(PP::simple_ostream& out) const noexcept = 0;

	public:
		constexpr virtual const descriptor& get_parent() const noexcept = 0;

		constexpr void print_name(PP::simple_ostream& out) const noexcept
		{
			print_name_before_parent(out);
			if (const descriptor& parent = get_parent(); &parent != this)
			{
				parent.print_name(out);
				out.write("::");
			}
			print_name_after_parent(out);
		}
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
