#include "stabilizer_circuit.h"
#include "gtest/gtest.h"

using StabilizerCircuit = CliffordTableaus::StabilizerCircuit;
using namespace std::complex_literals;

TEST(StabilizerCircuitTest, CreateRandomCircuitSet1) {
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_1.qasm",
            3,
            10,
            0,
            0,
            false,
            true,
            true
    );
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_2.qasm",
            5,
            100,
            10,
            20,
            false,
            true,
            true
    );
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_3.qasm",
            10,
            500,
            15,
            50,
            false,
            true,
            true
    );
}

TEST(StabilizerCircuitTest, TestRandomCircuitSet1) {


}
