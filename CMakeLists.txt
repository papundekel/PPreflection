cmake_minimum_required(VERSION 3.8)

project(PPreflection)

add_subdirectory(PPreflection)
add_subdirectory(TestProject)
target_compile_features(PPreflection PUBLIC cxx_std_20)
target_compile_features(TestProject PUBLIC cxx_std_20)
