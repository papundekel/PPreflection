#pragma once
#include "PP/size_t.hpp"
#include "PP/transform_view.hpp"
#include "PP/view.hpp"

#include "pragma_push.hpp"
#include "llvm/Support/raw_ostream.h"
#include "pragma_pop.hpp"

#include "for_each_with_delimiters.hpp"
#include "print_wrap.hpp"
#include "strings.hpp"

namespace PPreflector
{
	template <typename M>
	struct for_each_member_helper
	{
		const M& members;
	};

	class descriptor
	{
	public:
		virtual ~descriptor();

		virtual void print_name_header(llvm::raw_ostream& out) const = 0;
		virtual void print_name_own(llvm::raw_ostream& out) const = 0;
		virtual void print_name_foreign(llvm::raw_ostream& out) const = 0;
		virtual void print_metadata_implementation(llvm::raw_ostream& out) const = 0;

		virtual void print_qualified_name(llvm::raw_ostream& out) const = 0;
		virtual void print_name(llvm::raw_ostream& out) const = 0;

		void print_metadata_name(llvm::raw_ostream& out) const;
		void print_metadata_parent(llvm::raw_ostream& out) const;

		void print_metadata(llvm::raw_ostream& out) const;

		virtual const descriptor* get_parent(void* = nullptr) const = 0;

		void print_members(llvm::raw_ostream& out, auto& members, std::string_view members_name, std::string_view container_name) const
		{
			out << PPreflector::metadata_prefix << PPreflector::tags_namespace_name << members_name << "<" << PPREFLECTOR_PW(print_name_own, *this) << ">> = " << container_name << "<"
				<< for_each_member_helper(members) << ">;\n";
		}
	};

	template <typename M>
	llvm::raw_ostream& operator<<(llvm::raw_ostream& out, for_each_member_helper<M> fw)
	{
		for_each_with_delimiters([&out]
			(const descriptor& n)
			{
				out << 	"\n"
						"\t" << PPREFLECTOR_PW(print_name_foreign, n);
			}, [&out]
			()
			{
				out << ',';
			}, fw.members);

		return out;
	}

	auto as_descriptors_view(PP::concepts::view auto&& v)
	{
		return v | PP::transform([](const PPreflector::descriptor& d) -> auto& { return d; });
	}
}
