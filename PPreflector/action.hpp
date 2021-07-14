#pragma once
#include <memory>

// clang-format off
#include "pragma_push.hpp"
#include "clang/Frontend/FrontendAction.h"
#include "pragma_pop.hpp"
// clang-format on

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
