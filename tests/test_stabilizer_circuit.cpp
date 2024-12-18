#include "stabilizer_circuit.h"
#include "improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.h"
#include "gtest/gtest.h"

using StabilizerCircuit = CliffordTableaus::StabilizerCircuit;
using ImprovedStabilizerTableau = CliffordTableaus::ImprovedStabilizerTableau;
using namespace std::complex_literals;

TEST(StabilizerCircuitTest, CreateRandomCircuitSet1) {
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_1.qasm",
            5,
            10,
            0,
            0,
            false,
            true,
            true
    );
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_2.qasm",
            25,
            100,
            10,
            20,
            false,
            true,
            true
    );
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_3.qasm",
            100,
            500,
            15,
            50,
            false,
            true,
            true
    );
}

/**
 * This test doesn'T expect any specific output from the measurement.
 * It simply tests whether the circuits get executed without errors.
 */
TEST(StabilizerCircuitTest, TestImprovedStabilizerTableauNoError) {
    std::string measurement;
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();

    measurement = StabilizerCircuit::executeCircuit("bernstein_16.qasm", stabilizerTableau);
    std::cout << "First measurement: " << measurement << std::endl;
    measurement = StabilizerCircuit::executeCircuit("random_circuit_1.qasm", stabilizerTableau);
    std::cout << "Second measurement: " << measurement << std::endl;

    measurement = StabilizerCircuit::executeCircuit("random_circuit_2.qasm", stabilizerTableau);
    std::cout << "Third measurement: " << measurement << std::endl;
    measurement = StabilizerCircuit::executeCircuit("random_circuit_3.qasm", stabilizerTableau);
    std::cout << "Fourth measurement: " << measurement << std::endl;
}

/**
 * This test expects specific output from the measurement.
 */
TEST(StabilizerCircuitTest, TestImprovedStabilizerTableauOutput) {
    std::vector<int> failures = {};
    std::string measurement;
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();

    measurement = StabilizerCircuit::executeCircuit("test_circuit_1.qasm", stabilizerTableau);
    std::cout << "First measurement: " << measurement << std::endl;
    if (measurement != "11010") {
        failures.push_back(1);
    }

    measurement = StabilizerCircuit::executeCircuit("test_circuit_2.qasm", stabilizerTableau);
    std::cout << "Second measurement: " << measurement << std::endl;
    char q0 = measurement.at(0);
    char q1 = measurement.at(1);
    char q2 = measurement.at(2);
    char q3 = measurement.at(3);
    if (q0 != q1 || q2 != q3) {
        failures.push_back(2);
    }


    measurement = StabilizerCircuit::executeCircuit("test_circuit_3.qasm", stabilizerTableau);
    std::cout << "Third measurement: " << measurement << std::endl;
    if (measurement != "0000000000" &&
        measurement != "0000011111" &&
        measurement != "1111100000" &&
        measurement != "1111111111") {
        failures.push_back(3);
    }

    // All the fourth circuit has to do is not throw any errors.
    // The measurement result is irrelevant.
    try {
        measurement = StabilizerCircuit::executeCircuit("test_circuit_4.qasm", stabilizerTableau);
        std::cout << "Fourth measurement: " << measurement << std::endl;
    } catch (std::exception &e) {
        failures.push_back(4);
        std::cout << "Fourth measurement threw the following exception: " << e.what() << std::endl;
    }

    try {
        measurement = StabilizerCircuit::executeCircuit("test_circuit_5.qasm", stabilizerTableau);
        std::cout << "Fifth measurement: " << measurement << std::endl;
        if (measurement != "011") {
            failures.push_back(5);
        }
    } catch (std::exception &e) {
        failures.push_back(5);
        std::cout << "Fifth measurement threw the following exception: " << e.what() << std::endl;
    }

    if (!failures.empty()) {
        std::cout << "The following tests failed: ";
        for (int i = 0; i < failures.size() - 1; ++i) {
            std::cout << failures[i] << ", ";
        }
        std::cout << failures[failures.size() - 1] << std::endl;
        FAIL();
    }
}
