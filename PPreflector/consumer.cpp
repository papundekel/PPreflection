#include "consumer.hpp"

#include <fstream>

#include "pragma_pop.hpp"
#include "pragma_push.hpp"
#include "llvm/Support/raw_os_ostream.h"

PPreflector::consumer::consumer(clang::CompilerInstance& ci)
	: visitor_(ci)
{}

void PPreflector::consumer::HandleTranslationUnit(clang::ASTContext& context)
{
	auto* translation_unit_declaration = context.getTranslationUnitDecl();
	visitor_.TraverseDecl(translation_unit_declaration);
	visitor_.clear_temps();
	visitor_.remove_unwanted();

	std::ofstream out_s(
		std::string(get_main_file_name(context)).append(".meta"));

	llvm::raw_os_ostream out(out_s);

	// visitor_.print(llvm::outs());
	visitor_.print(out);
}

std::string_view PPreflector::consumer::get_main_file_name(
	clang::ASTContext& context)
{
	auto& source_manager = context.getSourceManager();

	return source_manager.getFileEntryForID(source_manager.getMainFileID())
		->getName();
}
