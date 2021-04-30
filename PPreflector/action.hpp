#pragma once
#include <memory>

#include "pragma_pop.hpp"
#include "pragma_push.hpp"
#include "clang/Frontend/FrontendAction.h"

#include "consumer.hpp"

namespace PPreflector
{
	class action : public clang::PluginASTAction
	{
		std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
			clang::CompilerInstance& CI,
			clang::StringRef) override final;
		bool ParseArgs(const clang::CompilerInstance&,
					   const std::vector<std::string>&) override final;
		clang::PluginASTAction::ActionType getActionType() override final;
	};
}
