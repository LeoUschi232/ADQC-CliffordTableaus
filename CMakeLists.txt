cmake_minimum_required(VERSION 3.29)
project(Clifford_Tableau)

set(CMAKE_CXX_STANDARD 26)

enable_testing()

# Ensure GTest is found
find_package(GTest REQUIRED)

# QuArray library
add_library(QuArrayLib src/quarray.cpp
        src/improved_simulation_of_stabilizer_circuits/subroutines.cpp
        src/improved_simulation_of_stabilizer_circuits/subroutines.h
        src/quantum_circuit_reader.cpp
        src/quantum_circuit_reader.h
        src/random_stabilizer_circuit.cpp
        src/random_stabilizer_circuit.h
)
target_include_directories(QuArrayLib PUBLIC src)

# Test executable
add_executable(test_quarray tests/test_quarray.cpp)
target_link_libraries(test_quarray GTest::gtest_main QuArrayLib)
add_test(NAME QuArrayTests COMMAND test_quarray)

# Main executable
add_executable(clifford_tableau main.cpp
)
target_link_libraries(clifford_tableau QuArrayLib)
