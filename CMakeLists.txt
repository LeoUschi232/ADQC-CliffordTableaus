cmake_minimum_required(VERSION 3.29)
project(Clifford_Tableau)

set(CMAKE_CXX_STANDARD 26)

add_executable(clifford_tableau main.cpp
        src/improved_simulation_of_stabilizer_circuits/qutils.cpp
        src/improved_simulation_of_stabilizer_circuits/qutils.h)
