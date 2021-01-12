cmake_minimum_required (VERSION 3.8)

add_executable(PPreflection main.cpp descriptor.cpp "types/known_bound_array_type.cpp" "dynamic_variable.hpp" "types/dynamic_reference_type.h" "functions/functions.h" "functions/implementations/implementations.h" "types/class_type.hpp" "types/types.hpp" "functions/implementations/basic_overloaded_named_function.h" "basic_named_descriptor.h" "functions/implementations/basic_static_member_function.h")
