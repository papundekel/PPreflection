#pragma once
#include <string_view>

// clang-format off
#include "pragma_push.hpp"
#include "clang/AST/ASTConsumer.h"
#include "pragma_pop.hpp"
// clang-format on

#include "visitor.hpp"

namespace PPreflector
{
	///
	/// @brief An AST consumer. A consumer is responsible for processing the AST
	/// of each translation unit.
	///
	class consumer : public clang::ASTConsumer
	{
		visitor visitor_;

	public:
		///
		/// @brief Constructs a new consumer.
		///
		/// @param ci A reference to the compiler.
		///
		explicit consumer(clang::CompilerInstance& ci);

		///
		/// @brief Processes a translation unit.
		///
		/// @param context A reference to the AST representing the TU.
		///
		void HandleTranslationUnit(clang::ASTContext& context) override final;

	private:
		static std::string_view get_main_file_name(clang::ASTContext& context);
	};
}
