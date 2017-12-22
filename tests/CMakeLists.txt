find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(ModuloInt modulo_int.cpp)
target_link_libraries(ModuloInt ${GTEST_BOTH_LIBRARIES})
