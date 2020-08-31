cmake_minimum_required(VERSION 3.8)

project(PPreflection)

add_subdirectory(Papo)
add_subdirectory(PPreflection)
add_subdirectory(TestProject)
target_compile_features(PPreflection PUBLIC cxx_std_20)
target_compile_features(TestProject PUBLIC cxx_std_20)

#set_target_properties(PPreflection PROPERTIES COMPILE_FLAGS "-fpermissive") 

#set_target_properties(PPreflection PROPERTIES COMPILE_FLAGS "-fpermissive -save-temps -masm=intel -fverbose-asm") 

add_dependencies(TestProject PPreflection)
add_dependencies(PPreflection PP)
