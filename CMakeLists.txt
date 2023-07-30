cmake_minimum_required(VERSION 3.25)
project(threads)

set(CMAKE_CXX_STANDARD 17)

set(SRC src)
set(INC ${CMAKE_CURRENT_SOURCE_DIR}/include)

list(APPEND SRC_LIST main.cpp ${SRC}/molecule.cpp)
add_executable(threads ${SRC_LIST})
target_include_directories(threads PUBLIC ${INC})
