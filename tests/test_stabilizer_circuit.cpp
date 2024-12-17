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


TEST(StabilizerCircuitTest, TestImprovedStabilizerTableau) {
    std::string measurement;
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();

    measurement = StabilizerCircuit::executeCircuit("test_circuit_1.qasm", stabilizerTableau);
    std::cout << "First measurement: " << measurement << std::endl;
    ASSERT_EQ(measurement, "11010");

    measurement = StabilizerCircuit::executeCircuit("test_circuit_2.qasm", stabilizerTableau);
    std::cout << "Second measurement: " << measurement << std::endl;
    char q0 = measurement.at(0);
    char q1 = measurement.at(1);
    char q2 = measurement.at(2);
    char q3 = measurement.at(3);
    ASSERT_EQ(q0, q1);
    ASSERT_EQ(q2, q3);

    measurement = StabilizerCircuit::executeCircuit("test_circuit_3.qasm", stabilizerTableau);
    std::cout << "Third measurement: " << measurement << std::endl;
    ASSERT_TRUE(
            measurement == "0000000000" ||
            measurement == "0000011111" ||
            measurement == "1111100000" ||
            measurement == "1111111111"
    );
}
