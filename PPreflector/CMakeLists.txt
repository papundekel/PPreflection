cmake_minimum_required (VERSION 3.8)

find_package(LLVM 12 REQUIRED CONFIG)

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})

add_llvm_library(PPreflector MODULE
"action.cpp"
"consumer.cpp"
"descriptor.cpp"
"Enum.cpp"
"global_namespace.cpp"
"main.cpp"
"Namespace.cpp"
"namespace_function.cpp"
"non_global_namespace.cpp"
"visitor.cpp"
PLUGIN_TOOL clang)

target_compile_features(PPreflector PUBLIC cxx_std_20)
set_target_properties(PPreflector PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=4")
target_include_directories(PPreflector PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../PP")
