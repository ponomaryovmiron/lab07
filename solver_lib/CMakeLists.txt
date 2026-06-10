add_library(solver STATIC
    solver.cpp
)

target_include_directories(solver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
