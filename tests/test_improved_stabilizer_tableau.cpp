#include "stabilizer_circuit.h"
#include "improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.h"
#include "gtest/gtest.h"

#include <exception>
#include <string>
#include <iostream>

using StabilizerCircuit = CliffordTableaus::StabilizerCircuit;
using ImprovedStabilizerTableau = CliffordTableaus::ImprovedStabilizerTableau;

/**
 * The following tests are refactored so that each circuit is tested separately.
 * The failure conditions and error messages remain the same as before.
 */

// From the first TEST block (TestImprovedStabilizerTableauNoError):

TEST(StabilizerCircuitTest, Bernstein16NoError) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string filename = "bernstein_16.qasm";
    try {
        StabilizerCircuit::executeCircuit(filename, stabilizerTableau);
    } catch (std::exception &e) {
        std::cout << "The following circuits failed: " << filename << std::endl;
        std::cout << "Circuit " << filename << " threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, RandomCircuit1NoError) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string filename = "random_circuit_1.qasm";
    try {
        StabilizerCircuit::executeCircuit(filename, stabilizerTableau);
    } catch (std::exception &e) {
        std::cout << "The following circuits failed: " << filename << std::endl;
        std::cout << "Circuit " << filename << " threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, RandomCircuit2NoError) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string filename = "random_circuit_2.qasm";
    try {
        StabilizerCircuit::executeCircuit(filename, stabilizerTableau);
    } catch (std::exception &e) {
        std::cout << "The following circuits failed: " << filename << std::endl;
        std::cout << "Circuit " << filename << " threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, RandomCircuit3NoError) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string filename = "random_circuit_3.qasm";
    try {
        StabilizerCircuit::executeCircuit(filename, stabilizerTableau);
    } catch (std::exception &e) {
        std::cout << "The following circuits failed: " << filename << std::endl;
        std::cout << "Circuit " << filename << " threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

// From the second TEST block (TestImprovedStabilizerTableauOutput):

TEST(StabilizerCircuitTest, TestCircuit1Output) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string expected = "11010";
    std::string actual;
    try {
        actual = StabilizerCircuit::executeCircuit("test_circuit_1.qasm", stabilizerTableau);
        if (actual != expected) {
            std::cout << "Test 1 failed." << std::endl;
            std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
            FAIL();
        }
    } catch (std::exception &e) {
        std::cout << "Test 1 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, TestCircuit2Output) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string expected = "00000|00001|00110|00111|11000|11001|11110|11111";
    std::string actual;
    try {
        actual = StabilizerCircuit::executeCircuit("test_circuit_2.qasm", stabilizerTableau);
        if (expected.find(actual) == std::string::npos) {
            std::cout << "Test 2 failed." << std::endl;
            std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
            FAIL();
        }
    } catch (std::exception &e) {
        std::cout << "Test 2 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, TestCircuit3Output) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string expected = "0000000000|0000011111|1111100000|1111111111";
    std::string actual;
    try {
        actual = StabilizerCircuit::executeCircuit("test_circuit_3.qasm", stabilizerTableau);
        if (expected.find(actual) == std::string::npos) {
            std::cout << "Test 3 failed." << std::endl;
            std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
            FAIL();
        }
    } catch (std::exception &e) {
        std::cout << "Test 3 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, TestCircuit4Output) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    try {
        StabilizerCircuit::executeCircuit("test_circuit_4.qasm", stabilizerTableau);
    } catch (std::exception &e) {
        std::cout << "Test 4 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, TestCircuit5Output) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string expected = "011";
    std::string actual;
    try {
        actual = StabilizerCircuit::executeCircuit("test_circuit_5.qasm", stabilizerTableau);
        if (actual != expected) {
            std::cout << "Test 5 failed." << std::endl;
            std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
            FAIL();
        }
    } catch (std::exception &e) {
        std::cout << "Test 5 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, TestCircuit6Output) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    try {
        StabilizerCircuit::executeCircuit("test_circuit_6.qasm", stabilizerTableau);
    } catch (std::exception &e) {
        std::cout << "Test 6 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}
