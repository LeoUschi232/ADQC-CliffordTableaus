cmake_minimum_required(VERSION 3.29)
project(Clifford_Tableau)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
enable_testing()

# Ensure GTest is found
find_package(GTest REQUIRED)

# QuArray library
add_library(CliffordTableausLib
        src/improved_simulation_of_stabilizer_circuits/subroutines.cpp
        src/improved_simulation_of_stabilizer_circuits/subroutines.h
        src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp
        src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.h
        src/stabilizer_circuit.cpp
        src/stabilizer_circuit.h
        src/stabilizer_tableau.cpp
        src/stabilizer_tableau.h
)
target_include_directories(CliffordTableausLib PUBLIC src)

# Test executable
add_executable(test_clifford_tableaus
        tests/test_improved_stabilizer_tableau.cpp
)
target_link_libraries(test_clifford_tableaus GTest::gtest_main CliffordTableausLib)
add_test(NAME CliffordTableausTests COMMAND test_clifford_tableaus)

# Main executable
add_executable(clifford_tableau main.cpp)

# Link the library
target_link_libraries(clifford_tableau CliffordTableausLib)

# Add include directories for proper header resolution
target_include_directories(clifford_tableau PUBLIC src
        src/improved_simulation_of_stabilizer_circuits
)
