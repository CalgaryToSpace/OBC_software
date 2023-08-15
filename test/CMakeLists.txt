cmake_minimum_required(VERSION 3.23)

set(This ExampleTests)
set(current_directory ".")


file(GLOB Sources "*.cpp")

# set(Sources
#     test_files    
# )

add_executable(
    ${This} ${Sources}
)

target_link_libraries(${This} PUBLIC
    gtest_main
    Example
    )

add_test(
    NAME ${This}
    COMMAND ${This}
)