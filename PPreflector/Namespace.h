#pragma once
#include <list>
#include <vector>

#include "PP/size_t.hpp"

// clang-format off
#include "pragma_push.hpp"
#include "clang/AST/Decl.h"
#include "pragma_pop.hpp"
// clang-format on

#include "descriptor.hpp"

namespace PPreflector
{
	class namespace_function;
	class non_global_namespace;
	class Enum;
	class Class;

	///
	/// @brief Represents a namespace.
	///
	class Namespace : public descriptor
	{
		PP::size_t depth;
		std::list<non_global_namespace> namespaces;
		std::vector<namespace_function> functions;
		std::vector<Enum> enums;
		std::list<Class> classes;

	protected:
		///
		/// @brief Construct a new Namespace object.
		///
		/// @param depth The number of parent namespaces.
		///
		Namespace(PP::size_t depth);

	public:
		void print_name_header(llvm::raw_ostream& out) const override final;
		void print_name_own(llvm::raw_ostream& out) const override final;
		void print_name_foreign(llvm::raw_ostream& out) const override final;

		///
		/// @brief Prints the name of the namespace. Used in the tag structure.
		///
		/// @param out The stream to output to.
		///
		virtual void print_layout_name(llvm::raw_ostream& out) const = 0;

		///
		/// @brief Prints the tag structure with this namespace as its root.
		///
		/// @param out The stream to output to.
		///
		void print_layout(llvm::raw_ostream& out) const;

		void print_metadata_members(
			llvm::raw_ostream& out) const override final;
		void print_metadata_traits(llvm::raw_ostream& out) const override;

		///
		/// @brief Registers a namespace as a nested entity of this namespace.
		///
		/// @param n The declaration of the namespace to register.
		/// @return A reference to the descriptor of the registered namespace.
		///
		non_global_namespace& add(clang::NamespaceDecl& n);
		///
		/// @brief Registers a function as a nested entity of this namespace.
		///
		/// @param n The declaration of the function to register.
		/// @return A reference to the descriptor of the registered function.
		///
		namespace_function& add(clang::FunctionDecl& f);
		///
		/// @brief Registers an enum as a nested entity of this namespace.
		///
		/// @param n The declaration of the enum to register.
		/// @return A reference to the descriptor of the registered enum.
		///
		Enum& add(clang::EnumDecl& e);
		///
		/// @brief Registers a class as a nested entity of this namespace.
		///
		/// @param n The declaration of the class to register.
		/// @return A reference to the descriptor of the registered class.
		///
		Class& add(clang::CXXRecordDecl& c);

		///
		/// @brief Removes the std namespace from registered entities. Only
		/// makes sense to call on the global namespace.
		///
		void remove_std();

		///
		/// @brief Prints a number of '\t' characters corresponding to the depth
		/// of nesting of this namespace.
		///
		void print_tabs(llvm::raw_ostream& out) const;

		///
		/// @brief Prints a the qualified name of the parent namespace with ::
		/// at the end, if it the parent isn't the global namespace.
		///
		/// @param out The stream to output to.
		///
		virtual void print_scoped_name_parent(llvm::raw_ostream& out) const = 0;

		///
		/// @brief Prints a the qualified name of this namespace with ::
		/// at the end, if this isn't the global namespace.
		///
		/// @param out The stream to output to.
		///
		virtual void print_scoped_name_as_parent(
			llvm::raw_ostream& out) const = 0;

	protected:
		///
		/// @brief Prints the tag type name of the parent namespace.
		///
		/// @param out The stream to output to.
		///
		virtual void print_name_parent(llvm::raw_ostream& out) const = 0;

	private:
		void print_namespaces(llvm::raw_ostream& out) const;
		void print_types(llvm::raw_ostream& out) const;
		void print_functions(llvm::raw_ostream& out) const;

		virtual void print_unscoped_name(llvm::raw_ostream& out) const = 0;
	};
}
