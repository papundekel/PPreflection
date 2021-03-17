#include "Namespace.hpp"

#include "PP/transform_view.hpp"
#include "PP/view_chain.hpp"

#include "Class.hpp"
#include "Enum.hpp"
#include "for_each_with_delimiters.hpp"
#include "non_global_namespace.hpp"
#include "print_wrap.hpp"
#include "strings.hpp"

PPreflector::Namespace::Namespace(PP::size_t depth)
	: descriptor()
	, depth(depth)
	, namespaces()
	, functions()
	, enums()
	, classes()
{}

void PPreflector::Namespace::print_metadata_name_header(llvm::raw_ostream& out) const
{
	print_name_simple(out);
}
void PPreflector::Namespace::print_metadata_name_own(llvm::raw_ostream& out) const
{
	print_name_full(out);
}
void PPreflector::Namespace::print_metadata_name_foreign(llvm::raw_ostream& out) const
{
	print_metadata_name_own(out);
}

void PPreflector::Namespace::print_name_full(llvm::raw_ostream& out) const
{
	print_name_parent(out);
	out << "::";
	print_name(out);
}

PPreflector::non_global_namespace& PPreflector::Namespace::add(clang::NamespaceDecl& n)
{
	return namespaces.emplace_back(depth + 1, n, *this);;
}

PPreflector::namespace_function& PPreflector::Namespace::add(clang::FunctionDecl& f)
{
	return functions.emplace_back(f, *this);
}

PPreflector::Enum& PPreflector::Namespace::add(clang::EnumDecl& e)
{
	return enums.emplace_back(*clang::dyn_cast_or_null<const clang::EnumType>(e.getTypeForDecl()), *this);
}

void PPreflector::Namespace::remove_std()
{
	namespaces.remove_if([](const non_global_namespace& n) { return n.is_std(); });
}

void PPreflector::Namespace::print_tabs(llvm::raw_ostream& out) const
{
	for (PP::size_t i = 0; i != depth + 1; ++i)
		out.write('\t');
}

void PPreflector::Namespace::print_layout(llvm::raw_ostream& out) const
{
	out << PPREFLECTOR_PW(print_tabs, *this) << "struct " << PPREFLECTOR_PW(print_name, *this);

	if (namespaces.empty())
	{
		out << ";\n";
	}
	else
	{
		out << "\n"
			<< PPREFLECTOR_PW(print_tabs, *this) << "{\n";

		for (const auto& n : namespaces)
			n.print_layout(out);

		out << PPREFLECTOR_PW(print_tabs, *this) << "};\n";
	}
}

namespace
{
	template <typename M>
	struct for_each_member_helper
	{
		const M& members;
	};
	template <typename M>
	llvm::raw_ostream& operator<<(llvm::raw_ostream& out, const for_each_member_helper<M>& fw)
	{
		for_each_with_delimiters([&out]
			(const PPreflector::descriptor& n)
			{
				out << 	"\n"
						"\t" << PPREFLECTOR_PW(print_metadata_name_foreign, n);
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

	void print_members(llvm::raw_ostream& out, const PPreflector::Namespace& n, auto& members, std::string_view members_name, std::string_view container_name)
	{
		out << PPreflector::metadata_prefix << PPreflector::tags_namespace_name << members_name << "<" << PPREFLECTOR_PW(print_name_full, n) << ">> = " << container_name << "<"
			<< for_each_member_helper(members)
			<< ">;\n";
	}
}

void PPreflector::Namespace::print_metadata_implementation(llvm::raw_ostream& out) const
{
	print_preamble(out);

	print_members(out, *this, functions, "functions", "PP::value_tuple");
	print_members(out, *this, enums, "types", "PP::type_tuple");
	print_members(out, *this, namespaces, "namespaces", "PP::type_tuple");

	for (const descriptor& d : PP::view_chain(as_descriptors_view(functions)) ^ as_descriptors_view(enums) ^ as_descriptors_view(namespaces))
		d.print_metadata(out);
}
