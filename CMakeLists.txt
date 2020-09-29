cmake_minimum_required(VERSION 3.8)

project(PPreflection)

add_subdirectory(PP)
add_subdirectory(PPreflection)
target_compile_features(PPreflection PUBLIC cxx_std_20)

#set_target_properties(PPreflection PROPERTIES COMPILE_FLAGS "-fpermissive") 

#set_target_properties(PPreflection PROPERTIES COMPILE_FLAGS "-fpermissive -save-temps -masm=intel -fverbose-asm") 

set_target_properties(PP PROPERTIES COMPILE_FLAGS "-fconcepts-diagnostics-depth=4")
set_target_properties(PPreflection PROPERTIES COMPILE_FLAGS "-fconcepts-diagnostics-depth=4")

add_dependencies(PPreflection PP)

target_include_directories(PPreflection PUBLIC "PP/PP")
