cmake_minimum_required(VERSION 3.13)

add_compile_options(-Wall -Wextra -pedantic -Werror)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

project(PPreflection)

add_subdirectory(PP)
add_subdirectory(PPreflection)
add_subdirectory(PPreflectiondemo)
add_subdirectory(PPreflector)

target_link_libraries(PPreflection PP)
target_link_libraries(PPreflectiondemo PPreflection)
