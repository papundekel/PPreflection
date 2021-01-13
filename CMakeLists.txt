cmake_minimum_required(VERSION 3.8)

project(PPreflection)

add_subdirectory(PP)
add_subdirectory(PPreflection)
target_compile_features(PPreflection PUBLIC cxx_std_20)

set_target_properties(PPreflection PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=4")

add_dependencies(PPreflection PP)

target_include_directories(PPreflection PUBLIC "PP/PP")
