cmake_minimum_required (VERSION 3.8)

add_executable(PPreflectiondemo
"animals.cpp"
"main.cpp"
"reactions.cpp"
"visitor.cpp"
)
target_compile_features(PPreflectiondemo PUBLIC cxx_std_20)
set_target_properties(PPreflectiondemo PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=5")
target_include_directories(PPreflectiondemo PUBLIC "${CMAKE_CURRENT_LIST_DIR}/.." "${CMAKE_CURRENT_LIST_DIR}/../PP")
