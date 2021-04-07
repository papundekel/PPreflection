#pragma once
#include "pragma_push.hpp"
#include "clang/AST/DeclCXX.h"
#include "pragma_pop.hpp"

#include "function.hpp"

namespace PPreflector
{
	llvm::raw_ostream& operator<<(llvm::raw_ostream& out, clang::Qualifiers cv);
	llvm::raw_ostream& operator<<(llvm::raw_ostream& out, clang::RefQualifierKind ref);

	template <typename MDecl>
	requires PP::concepts::derived_from<MDecl, clang::CXXMethodDecl>
	class member_function : public function<MDecl>
	{
	public:
		using function<MDecl>::function;

		void print_name_header(llvm::raw_ostream& out) const override final
		{
			out << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, *this) << "(" << PPREFLECTOR_MEMBER_PRINT(print_parameter_types, *this) << ")";
	
			const auto& decl = this->get_node();

			auto cv = decl.getMethodQualifiers();

			if (cv.hasConst())
				out << " const";
			if (cv.hasVolatile())
				out << " volatile";

			auto ref = decl.getRefQualifier();

			if (ref == clang::RefQualifierKind::RQ_LValue)
				out << "&";
			else if (ref == clang::RefQualifierKind::RQ_RValue)
				out << "&&";
		}

		void print_name_own(llvm::raw_ostream& out) const override final
		{
			out << this->printer_value_t(PPREFLECTOR_MEMBER_PRINT(print_name_foreign, *this));
		}

		void print_name_foreign(llvm::raw_ostream& out) const override final
		{
			const auto& decl = this->get_node();

			out << "PPreflection::overload_member_caster<" << decl.getMethodQualifiers() << ", " << decl.getRefQualifier() << PPREFLECTOR_MEMBER_PRINT(print_parameter_types_leading_comma, *this) << ">(::" << PPREFLECTOR_MEMBER_PRINT(print_qualified_name, *this) << ")";
		}
	};
}
