cmake_minimum_required (VERSION 3.8)

add_library(PPreflectionlib
"PPany_view.cpp"
"descriptor.cpp"
"types/known_bound_array_type.cpp"
)
target_compile_features(PPreflectionlib PUBLIC cxx_std_20)

add_executable(PPreflection
"main.cpp"
)
target_compile_features(PPreflection PUBLIC cxx_std_20)

target_link_libraries(PPreflection PPreflectionlib)

target_precompile_headers(PPreflectionlib PUBLIC
"PPany_view.hpp"
)
