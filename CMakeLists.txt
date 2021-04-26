cmake_minimum_required(VERSION 3.13)

add_compile_options(
	-Wall
	-Wextra
	-pedantic
	-Werror
#	-pg
)
#add_link_options(-pg)

project(PPreflection)

add_subdirectory(PP)
add_subdirectory(PPreflection)
add_subdirectory(PPreflectiondemo)
add_subdirectory(PPreflector)

target_link_libraries(PPreflection PP)
target_link_libraries(PPreflectiondemo PPreflection)
