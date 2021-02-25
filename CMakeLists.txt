cmake_minimum_required(VERSION 3.13)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

project(PPreflection)

add_subdirectory(PP)
add_subdirectory(PPreflection)

target_link_libraries(PPreflectionlib PPlib)

set_target_properties(PPreflectionlib PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=4")
set_target_properties(PPreflection PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=4")

target_include_directories(PPreflectionlib PUBLIC "PP/PP")
target_include_directories(PPreflection PUBLIC "PP/PP")
