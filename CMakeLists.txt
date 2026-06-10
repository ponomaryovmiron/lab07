cmake_minimum_required(VERSION 3.10)

project(print)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(print STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp
)

target_include_directories(print PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(example1
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/example1.cpp
)

add_executable(example2
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/example2.cpp
)

target_link_libraries(example1 print)
target_link_libraries(example2 print)

install(TARGETS print example1 example2
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
)
