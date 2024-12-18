#include "stabilizer_circuit.h"
#include "improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.h"
#include "gtest/gtest.h"

#include <exception>
#include <vector>
#include <map>

using StabilizerCircuit = CliffordTableaus::StabilizerCircuit;
using ImprovedStabilizerTableau = CliffordTableaus::ImprovedStabilizerTableau;
using namespace std::complex_literals;

/**
 * This test doesn't expect any specific output from the measurement.
 * It simply tests whether the circuits get executed without errors.
 */
TEST(StabilizerCircuitTest, TestImprovedStabilizerTableauNoError) {
    std::vector<std::string> filenames = {
            "bernstein_16.qasm",
            "random_circuit_1.qasm",
            "random_circuit_2.qasm",
            "random_circuit_3.qasm"
    };

    std::map<std::string, std::string> failures = {};
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();

    for (const std::string &filename: filenames) {
        try {
            StabilizerCircuit::executeCircuit(filename, stabilizerTableau);
        } catch (std::exception &e) {
            failures[filename] = e.what();
        }
    }
    if (!failures.empty()) {
        auto failures_iterator = failures.begin();
        std::cout << "The following circuits failed: " << failures_iterator->first;
        while (++failures_iterator != failures.end()) {
            std::cout << ", " << failures_iterator->first;
        }
        std::cout << std::endl;
        for (auto const &[filename, error]: failures) {
            std::cout << "Circuit " << filename << " threw exception: " << error << std::endl;
        }
        FAIL();
    }
}

/**
 * This test expects specific output from the measurement.
 */
TEST(StabilizerCircuitTest, TestImprovedStabilizerTableauOutput) {
    // The tuple consists of these attributes in the following order:
    // 1. Test circuit index
    // 2. [optional] String of thrown exception
    // 3. Expected measurement result
    // 4. [optional] Actual measurement result
    std::vector<std::tuple<int, std::string, std::string, std::string>> failures = {};
    std::string actual;
    std::string expected;
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();

    try {
        expected = "11010";
        actual = StabilizerCircuit::executeCircuit("test_circuit_1.qasm", stabilizerTableau);
        if (actual != expected) {
            failures.emplace_back(1, "", expected, actual);
        }
    } catch (std::exception &e) {
        failures.emplace_back(1, e.what(), expected, "");
    }


    try {
        expected = "00000|00001|00110|00111|11000|11001|11110|11111";
        actual = StabilizerCircuit::executeCircuit("test_circuit_2.qasm", stabilizerTableau);

        // Check if actual is a substring of expected.
        if (expected.find(actual) == std::string::npos) {
            failures.emplace_back(2, "", expected, actual);
        }
    } catch (std::exception &e) {
        failures.emplace_back(2, e.what(), expected, "");
    }

    try {
        expected = "0000000000|0000011111|1111100000|1111111111";
        actual = StabilizerCircuit::executeCircuit("test_circuit_3.qasm", stabilizerTableau);

        // Check if actual is a substring of expected.
        if (expected.find(actual) == std::string::npos) {
            failures.emplace_back(2, "", expected, actual);
        }
    } catch (std::exception &e) {
        failures.emplace_back(2, e.what(), expected, "");
    }

    // All the fourth circuit has to do is not throw any errors.
    // The measurement result is irrelevant.
    try {
        StabilizerCircuit::executeCircuit("test_circuit_4.qasm", stabilizerTableau);
    } catch (std::exception &e) {
        failures.emplace_back(4, e.what(), "", "");
    }

    try {
        expected = "011";
        actual = StabilizerCircuit::executeCircuit("test_circuit_5.qasm", stabilizerTableau);
        if (actual != expected) {
            failures.emplace_back(5, "", expected, actual);
        }
    } catch (std::exception &e) {
        failures.emplace_back(5, e.what(), expected, "");
    }

    if (!failures.empty()) {
        std::cout << "The following tests failed: ";
        for (int i = 0; i < failures.size() - 1; ++i) {
            std::cout << std::get<0>(failures[i]) << ", ";
        }
        std::cout << std::get<0>(failures[failures.size() - 1]) << std::endl;

        for (auto failure: failures) {
            if (!std::get<1>(failure).empty()) {
                std::cout << "Test " << std::get<0>(failure) << " threw exception: " << std::get<1>(failure)
                          << std::endl;
            } else {
                std::cout << "Test " << std::get<0>(failure) << " failed.\n"
                          << "Expected: " << std::get<2>(failure) << "\n"
                          << "  Actual: " << std::get<3>(failure) << std::endl;
            }
        }
        FAIL();
    }
}
