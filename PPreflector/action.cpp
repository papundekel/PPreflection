#include "action.hpp"

std::unique_ptr<clang::ASTConsumer> PPreflector::action::CreateASTConsumer(
	clang::CompilerInstance& CI,
	clang::StringRef)
{
	auto& pp = CI.getPreprocessor();
	auto* mi = pp.AllocateMacroInfo({});
	pp.appendDefMacroDirective(pp.getIdentifierInfo("PPREFLECTOR_GUARD"), mi);

	return std::make_unique<consumer>(CI);
}

bool PPreflector::action::ParseArgs(const clang::CompilerInstance&,
									const std::vector<std::string>&)
{
	return true;
}

clang::PluginASTAction::ActionType PPreflector::action::getActionType()
{
	return clang::PluginASTAction::AddAfterMainAction;
}
