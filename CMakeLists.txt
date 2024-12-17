cmake_minimum_required(VERSION 3.29)
project(Clifford_Tableau)

set(CMAKE_CXX_STANDARD 26)

enable_testing()

# Ensure GTest is found
find_package(GTest REQUIRED)

# QuArray library
add_library(QuArrayLib
        src/quarray.cpp
        src/quarray.h
        src/improved_simulation_of_stabilizer_circuits/subroutines.cpp
        src/improved_simulation_of_stabilizer_circuits/subroutines.h
        src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp
        src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.h
        src/stabilizer_circuit.cpp
        src/stabilizer_circuit.h
        src/stabilizer_tableau.h
        src/stabilizer_tableau.cpp
)
target_include_directories(QuArrayLib PUBLIC src)

# Test executable
add_executable(test_quarray
        tests/test_quarray.cpp
        tests/test_stabilizer_circuit.cpp
)
target_link_libraries(test_quarray GTest::gtest_main QuArrayLib)
add_test(NAME QuArrayTests COMMAND test_quarray)

# Main executable
add_executable(clifford_tableau main.cpp)

# Link the library
target_link_libraries(clifford_tableau QuArrayLib)

# Add include directories for proper header resolution
target_include_directories(clifford_tableau PUBLIC
        src
        src/improved_simulation_of_stabilizer_circuits
)
