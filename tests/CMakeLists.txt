add_executable(ModuloInt modulo_int.cpp)
add_executable(Chessboard chessboard.cpp)
target_link_libraries(ModuloInt ${GTEST_BOTH_LIBRARIES})
target_link_libraries(Chessboard ${GTEST_BOTH_LIBRARIES})
