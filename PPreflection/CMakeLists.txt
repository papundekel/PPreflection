cmake_minimum_required (VERSION 3.8)

add_library(PPreflection
"PPany_view.cpp"
"descriptor.cpp"
"dynamic_variable.cpp"
"types/known_bound_array_type.cpp"
)
target_compile_features(PPreflection PUBLIC cxx_std_20)
set_target_properties(PPreflection PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=4")
target_include_directories(PPreflection PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../PP")

target_precompile_headers(PPreflection PUBLIC
"PPany_view.hpp"
)
