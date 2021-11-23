cmake_minimum_required(VERSION 3.13)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "..." FORCE)

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
add_subdirectory(PPreflector)

target_link_libraries(PPreflection PP)

install(FILES "${CMAKE_SOURCE_DIR}/generate_metadata.sh" DESTINATION "PPreflection")
