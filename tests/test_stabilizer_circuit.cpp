#include "stabilizer_circuit.h"
#include "improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.h"
#include "gtest/gtest.h"

using StabilizerCircuit = CliffordTableaus::StabilizerCircuit;
using ImprovedStabilizerTableau = CliffordTableaus::ImprovedStabilizerTableau;
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

    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();

    auto filename = "custom_circuit_2.qasm";
    auto final_measurement = StabilizerCircuit::executeCircuit(filename, stabilizerTableau);
    std::cout << final_measurement << std::endl;

}

TEST(StabilizerCircuitTest, TestCustomCircuitSet1) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    auto final_measurement = StabilizerCircuit::executeCircuit("custom_circuit_2.qasm", stabilizerTableau);
    std::cout << final_measurement << std::endl;
}
