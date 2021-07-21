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
	///
	/// @brief Base class for all reflected entities. Represents one entity of
	/// the source code.
	///
	///
	class descriptor
	{
	public:
		virtual ~descriptor() = default;

		///
		/// @brief Prints the name of the entity. Used in the header metadata
		/// section.
		///
		/// @param out The stream to output to.
		///
		virtual void print_name_header(llvm::raw_ostream& out) const = 0;

		///
		/// @brief Prints the name of the entity. Used when the entity refers to
		/// itself.
		///
		/// @param out The stream to output to.
		///
		virtual void print_name_own(llvm::raw_ostream& out) const = 0;

		///
		/// @brief Prints the name of the entity. USed when the entity is
		/// referred to by another entity.
		///
		/// @param out The stream to output to.
		///
		virtual void print_name_foreign(llvm::raw_ostream& out) const = 0;

		///
		/// @brief Prints the metadata of all member entities.
		///
		/// @param out The stream to output to.
		///
		virtual void print_metadata_members(llvm::raw_ostream& out) const = 0;

		///
		/// @brief Prints the metadata about entity information other than its
		/// descriptor.
		///
		/// @param out The stream to output to.
		///
		virtual void print_metadata_traits(llvm::raw_ostream& out) const = 0;

		///
		/// @brief Prints the metadata about entity descriptor.
		///
		/// @param out The stream to output to.
		///
		virtual void print_metadata_object(llvm::raw_ostream& out) const = 0;

		///
		/// @brief Prints the full qualified name of the entity.
		///
		/// @param out The stream to output to.
		///
		virtual void print_qualified_name(llvm::raw_ostream& out) const = 0;

		///
		/// @brief Prints the name of the entity.
		///
		/// @param out The stream to output to.
		///
		virtual void print_name(llvm::raw_ostream& out) const = 0;

		///
		/// @brief Prints the metadata about the name of the entity.
		///
		/// @param out The stream to output to.
		///
		void print_metadata_name(llvm::raw_ostream& out) const;

		///
		/// @brief Prints the metadata about the name of the entity.
		///
		/// @param out The stream to output to.
		///
		void print_metadata_parent(llvm::raw_ostream& out) const;

		///
		/// @brief Prints all metadata about the entity.
		///
		/// @param out The stream to output to.
		///
		void print_metadata(llvm::raw_ostream& out) const;

		///
		/// @brief Gets the parent entity descriptor.
		///
		/// @return Pointer to the parent entity descriptor.
		/// @retval nullptr This entity has no parent.
		///
		virtual const descriptor* get_parent(void* = nullptr) const;

	protected:
		///
		/// @brief Printer object for printing a string contained in a @ref
		/// PP::value_tuple_t.
		///
		static constexpr auto printer_value_tuple =
			container_printer<"PP::value_tuple<"_str, ">"_str>;

		///
		/// @brief Printer object for printing a string contained in a @ref
		/// PP::type_tuple_t.
		///
		static constexpr auto printer_type_tuple =
			container_printer<"PP::type_tuple<"_str, ">"_str>;

		///
		/// @brief Printer object for printing a string contained in a @ref
		/// PP::make_tuple.
		///
		static constexpr auto printer_make_tuple =
			container_printer<"PP::make_tuple("_str, ")"_str>;

		///
		/// @brief Printer object for printing a string contained in a @ref
		/// PP::type_t.
		///
		static constexpr auto printer_type =
			container_printer<"PP::type<"_str, ">"_str>;

		///
		/// @brief Printer object for printing a string contained in a @ref
		/// PP::value_t.
		///
		static constexpr auto printer_value_t =
			container_printer<"PP::value_t<"_str, ">"_str>;

		///
		/// @brief Printer object for printing a string contained in a metadata
		/// specialized variable
		///
		static constexpr auto printer_metadata = container_printer<
			"\ttemplate <> constexpr inline auto metadata<"_str,
			"> = "_str>;

		///
		/// @brief Printer object for printing a string contained in a metadata
		/// variable specialized for a descriptor
		///
		static constexpr auto printer_metadata_descriptor = container_printer<
			"\ttemplate <> constexpr inline auto metadata<tags::descriptor<"_str,
			">> = "_str>;

		///
		/// @brief Printer object for printing a string contained in the @ref
		/// PP::basic_string_view string literal.
		///
		static constexpr auto printer_sv =
			container_printer<"\""_str, "\"_sv"_str>;

		///
		/// @brief Prints member entity names inside a specified container.
		///
		/// @tparam tag_name
		/// @param out The stream to output to.
		/// @param members A container with the member descriptors.
		/// @param container_printer A printer object specifying the name of the
		/// container.
		/// @return llvm::raw_ostream&
		///
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

	namespace detail
	{
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

}

template <auto tag_name>
llvm::raw_ostream& PPreflector::descriptor::print_members(
	llvm::raw_ostream& out,
	const auto& members,
	const auto& container_printer) const
{
	return out << printer_metadata(metadata_tag_printer<tag_name>(
					  PPREFLECTOR_MEMBER_PRINT(print_name_own, *this)))
	           << container_printer(detail::for_each_member_helper(members))
	           << ";";
}
