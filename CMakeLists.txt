cmake_minimum_required(VERSION 3.23)

set(This Example)
set(project_root ".")


project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

file(GLOB Headers ${project_root}/headers/*)
file(GLOB Sources ${project_root}/actualCode/*)



# set(
#     Headers
#     Example.hpp
#     Example2.hpp
# )
# set(
#     Sources
#     Example.cpp
#     Example2.cpp
# )


add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)