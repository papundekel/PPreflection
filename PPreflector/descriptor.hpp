#pragma once
#include "PP/size_t.hpp"
#include "PP/transform_view.hpp"
#include "PP/view.hpp"

// clang-format off
#include "pragma_push.hpp"
#include "llvm/Support/raw_ostream.h"
#include "pragma_pop.hpp"
// clang-format on

#include "for_each_with_delimiters.hpp"
#include "printers.hpp"

namespace PPreflector
{
	class descriptor
	{
	public:
		virtual ~descriptor();

		virtual void print_name_header(llvm::raw_ostream& out) const = 0;
		virtual void print_name_own(llvm::raw_ostream& out) const = 0;
		virtual void print_name_foreign(llvm::raw_ostream& out) const = 0;

		virtual void print_metadata_members(llvm::raw_ostream& out) const = 0;
		virtual void print_metadata_traits(llvm::raw_ostream& out) const = 0;
		virtual void print_metadata_object(llvm::raw_ostream& out) const = 0;

		virtual void print_qualified_name(llvm::raw_ostream& out) const = 0;
		virtual void print_name(llvm::raw_ostream& out) const = 0;

		void print_metadata_name(llvm::raw_ostream& out) const;
		void print_metadata_parent(llvm::raw_ostream& out) const;

		void print_metadata(llvm::raw_ostream& out) const;

		virtual const descriptor* get_parent(void* = nullptr) const;

	protected:
		static constexpr auto printer_value_tuple =
			container_printer<"PP::value_tuple<"_str, ">"_str>;
		static constexpr auto printer_type_tuple =
			container_printer<"PP::type_tuple<"_str, ">"_str>;
		static constexpr auto printer_make_tuple =
			container_printer<"PP::make_tuple("_str, ")"_str>;
		static constexpr auto printer_type =
			container_printer<"PP::type<"_str, ">"_str>;
		static constexpr auto printer_value_t =
			container_printer<"PP::value_t<"_str, ">"_str>;
		static constexpr auto printer_metadata = container_printer<
			"\ttemplate <> constexpr inline auto metadata<X(), "_str,
			"> = "_str>;
		static constexpr auto printer_sv =
			container_printer<"\""_str, "\"_sv"_str>;

		template <auto tag_name>
		llvm::raw_ostream& print_members(llvm::raw_ostream& out,
										 const auto& members,
										 const auto& container_printer) const;
	};

	auto as_descriptors_view(PP::concepts::view auto&& v)
	{
		return v | PP::transform([](const PPreflector::descriptor& d) -> auto&
								 {
									 return d;
								 });
	}

	template <typename M>
	struct for_each_member_helper
	{
		const M& members;

		void operator()(llvm::raw_ostream& out) const
		{
			for_each_with_delimiters(
				[&out](const descriptor& n)
				{
					// clang-format off
					out << "\n"
						<< "\t\t" << PPREFLECTOR_MEMBER_PRINT(print_name_foreign, n);
					// clang-format on
				},
				[&out]()
				{
					out << ',';
				},
				members);
		}
	};
}

template <auto tag_name>
llvm::raw_ostream& PPreflector::descriptor::print_members(
	llvm::raw_ostream& out,
	const auto& members,
	const auto& container_printer) const
{
	return out << printer_metadata(metadata_tag_printer<tag_name>(
					  PPREFLECTOR_MEMBER_PRINT(print_name_own, *this)))
			   << container_printer(for_each_member_helper(members)) << ";";
}
