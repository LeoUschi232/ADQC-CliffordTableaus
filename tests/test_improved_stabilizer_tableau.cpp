#include "stabilizer_circuit.h"
#include "improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.h"
#include "gtest/gtest.h"

#include <exception>
#include <string>
#include <iostream>

using StabilizerCircuit = CliffordTableaus::StabilizerCircuit;
using ImprovedStabilizerTableau = CliffordTableaus::ImprovedStabilizerTableau;

TEST(StabilizerCircuitTest, Bernstein16NoError) {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string filename = "bernstein_16.qasm";
    std::string expected = "1111111111111111";
    std::string actual;
    try {
        actual = StabilizerCircuit::executeCircuit(filename, stabilizerTableau);
        if (actual != expected) {
            std::cout << "Bernstein 16 failed." << std::endl;
            std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
            FAIL();
        }
    } catch (std::exception &e) {
        std::cout << "The following circuits failed: " << filename << std::endl;
        std::cout << "Circuit " << filename << " threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, RandomCircuit1NoError) {
    auto nr_shots = 500;
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string filename = "random_circuit_1.qasm";
    std::string expected = "000|010|100|110";
    std::string actual;
    try {
        for (int shot = 1; shot <= nr_shots; shot++) {
            actual = StabilizerCircuit::executeCircuit(filename, stabilizerTableau);
            if (expected.find(actual) == std::string::npos) {
                std::cout << "Random 1 failed on shot: " << shot << std::endl;
                std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
                FAIL();
            }
        }
    } catch (std::exception &e) {
        std::cout << "The following circuits failed: " << filename << std::endl;
        std::cout << "Circuit " << filename << " threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, RandomCircuit2NoError) {
    auto nr_shots = 500;
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string filename = "random_circuit_2.qasm";
    std::string expected = "00110|01100|10011|11001";
    std::string actual;
    try {
        for (int shot = 1; shot <= nr_shots; shot++) {
            actual = StabilizerCircuit::executeCircuit(filename, stabilizerTableau);
            if (expected.find(actual) == std::string::npos) {
                std::cout << "Random 2 failed on shot: " << shot << std::endl;
                std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
                FAIL();
            }
        }
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
    auto nr_shots = 500;
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string expected = "00000|00001|00110|00111|11000|11001|11110|11111";
    std::string actual;
    try {
        for (int shot = 1; shot <= nr_shots; shot++) {
            actual = StabilizerCircuit::executeCircuit("test_circuit_2.qasm", stabilizerTableau);
            if (expected.find(actual) == std::string::npos) {
                std::cout << "Test 2 failed on shot: " << shot << std::endl;
                std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
                FAIL();
            }
        }
    } catch (std::exception &e) {
        std::cout << "Test 2 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, TestCircuit3Output) {
    auto nr_shots = 500;
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string expected = "0000000000|0000011111|1111100000|1111111111";
    std::string actual;
    try {
        for (int shot = 1; shot <= nr_shots; shot++) {
            actual = StabilizerCircuit::executeCircuit("test_circuit_3.qasm", stabilizerTableau);
            if (expected.find(actual) == std::string::npos) {
                std::cout << "Test 3 failed on shot: " << shot << std::endl;
                std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
                FAIL();
            }
        }
    } catch (std::exception &e) {
        std::cout << "Test 3 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, TestCircuit4Output) {
    // The fourth test circuit needs only to run without errors.
    // It is not expected to produce any specific output format.
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

TEST(StabilizerCircuitTest, TestCircuit7Output) {
    auto nr_shots = 500;
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string expected = "****00**";
    std::string actual;
    try {
        // For this circuit, the qubits at indices 0,1,2,3,6,7 are indeterminate.
        // Only qubits 4 and 5 should 100% measure to be |0〉.
        for (int shot = 1; shot <= nr_shots; shot++) {
            actual = StabilizerCircuit::executeCircuit("test_circuit_7.qasm", stabilizerTableau);
            if (actual[4] != expected[4] && actual[5] != expected[5]) {
                std::cout << "Test 7 failed on shot: " << shot << std::endl;
                std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
                FAIL();
            }
        }
    } catch (std::exception &e) {
        std::cout << "Test 7 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, TestCircuit8Output) {
    // The seventh test circuit is based on the fourth test circuit and obeys the same conditions.
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    try {
        StabilizerCircuit::executeCircuit("test_circuit_8.qasm", stabilizerTableau);
    } catch (std::exception &e) {
        std::cout << "Test 8 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}


TEST(StabilizerCircuitTest, TestCircuit9Output) {
    auto nr_shots = 500;
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string expected = "0000|0001|0010|0011|1100|1101|1110|1111";
    std::string actual;
    try {
        for (int shot = 1; shot <= nr_shots; shot++) {
            actual = StabilizerCircuit::executeCircuit("test_circuit_9.qasm", stabilizerTableau);
            if (expected.find(actual) == std::string::npos) {
                std::cout << "Test 9 failed on shot: " << shot << std::endl;
                std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
                FAIL();
            }
        }
    } catch (std::exception &e) {
        std::cout << "Test 9 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}

TEST(StabilizerCircuitTest, TestCircuit10ßOutput) {
    auto nr_shots = 500;
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    std::string expected = "0000|0001|0010|0011|1100|1101|1110|1111";
    std::string actual;
    try {
        for (int shot = 1; shot <= nr_shots; shot++) {
            actual = StabilizerCircuit::executeCircuit("test_circuit_9.qasm", stabilizerTableau);
            if (expected.find(actual) == std::string::npos) {
                std::cout << "Test 10 failed on shot: " << shot << std::endl;
                std::cout << "Expected: " << expected << std::endl << "  Actual: " << actual << std::endl;
                FAIL();
            }
        }
    } catch (std::exception &e) {
        std::cout << "Test 10 threw exception: " << e.what() << std::endl;
        FAIL();
    }
}