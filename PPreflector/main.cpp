#include "pragma_pop.hpp"
#include "pragma_push.hpp"
#include "clang/Frontend/FrontendPluginRegistry.h"

#include "action.hpp"

static clang::FrontendPluginRegistry::Add<PPreflector::action> X("", "");
