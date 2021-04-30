#pragma once
#include <string_view>

#include "PP/concepts/fundamental_types.hpp"
#include "PP/view_copy.hpp"

#include "pragma_pop.hpp"
#include "pragma_push.hpp"
#include "llvm/Support/raw_ostream.h"

namespace PPreflector
{
	template <typename P>
	concept printer_enabled = requires(const P p, llvm::raw_ostream& out)
	{
		{
			p(out)
		}
		->PP::concepts::void_type;
	};

	llvm::raw_ostream& operator<<(llvm::raw_ostream&		  out,
								  const printer_enabled auto& p)
	{
		p(out);
		return out;
	}

	template <typename F, typename T>
	struct print_member_wrap
	{
		F		 printing_function;
		const T& printer;

		void operator()(llvm::raw_ostream& out) const
		{
			printing_function(out, printer);
		}
	};

#define PPREFLECTOR_MEMBER_PRINT(function_name, object)                        \
	(::PPreflector::print_member_wrap(                                         \
		[](llvm::raw_ostream& out, auto& printer)                              \
		{                                                                      \
			printer.function_name(out);                                        \
		},                                                                     \
		object))

	template <PP::size_t count>
	struct constant_string
	{
		char chars[count];

		constexpr constant_string(const char (&string)[count + 1]) noexcept
		{
			PP::view_copy(chars, string);
		}
	};
	template <PP::size_t count>
	constant_string(const char (&)[count]) -> constant_string<count - 1>;

	template <PP::size_t count>
	llvm::raw_ostream& operator<<(llvm::raw_ostream&			out,
								  const constant_string<count>& str)
	{
		out.write(str.chars, count);
		return out;
	}

	template <constant_string s>
	constexpr auto operator""_str()
	{
		return s;
	}

	template <auto prefix, auto suffix>
	constexpr inline auto container_printer = [](const auto& inner_printer)
	{
		return [&inner_printer](llvm::raw_ostream& out)
		{
			out << prefix << inner_printer << suffix;
		};
	};

	template <auto prefix>
	constexpr inline auto metadata_tag_printer = [](const auto& inner_printer)
	{
		return [&inner_printer](llvm::raw_ostream& out)
		{
			out << "PPreflection::tags::" << prefix << "<" << inner_printer
				<< ">";
		};
	};
}
