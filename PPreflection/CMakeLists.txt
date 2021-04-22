cmake_minimum_required (VERSION 3.8)

add_library(PPreflection
"descriptor.cpp"
"dynamic_object.cpp"
"dynamic_variable.cpp"
"functions/member_function.cpp"
"types/known_bound_array_type.cpp"
"types/null_type.cpp"
)
target_compile_features(PPreflection PUBLIC cxx_std_20)

if(CMAKE_COMPILER_IS_GNUCXX)
set_target_properties(PPreflection PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=6")
endif()

target_include_directories(PPreflection PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../PP")
