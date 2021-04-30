#pragma once
#include <string_view>

#include "pragma_pop.hpp"
#include "pragma_push.hpp"
#include "clang/AST/ASTConsumer.h"

#include "visitor.hpp"

namespace PPreflector
{
	class consumer : public clang::ASTConsumer
	{
		visitor visitor_;

	public:
		explicit consumer(clang::CompilerInstance& ci);

		void HandleTranslationUnit(clang::ASTContext& context) override final;

	private:
		static std::string_view get_main_file_name(clang::ASTContext& context);
	};
}
