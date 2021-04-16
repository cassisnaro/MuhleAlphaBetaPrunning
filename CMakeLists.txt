cmake_minimum_required(VERSION 3.16)
project(MuhleAlphaBeta)

set(CMAKE_CXX_STANDARD 17)

add_executable(MuhleAlphaBeta main.cpp MuhleState.cpp MuhleState.h Action.cpp Action.h)