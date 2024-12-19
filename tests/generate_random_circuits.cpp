#include "stabilizer_circuit.h"
#include "improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.h"
#include "gtest/gtest.h"

#include <exception>
#include <string>
#include <iostream>

using StabilizerCircuit = CliffordTableaus::StabilizerCircuit;
using ImprovedStabilizerTableau = CliffordTableaus::ImprovedStabilizerTableau;

// /**
//  * Create a random stabilizer circuit and write it to a file.
//  * @param circuit_filename Name of the file to write the circuit to.
//  * @param n_qubits Number of qubits in the system.
//  * @param depth Number of gates in the circuit.
//  * @param gate_seed Seed for the random number generator for selecting gates.
//  * @param qubit_seed Seed for the random number generator for selecting qubits.
//  * @param allow_intermediate_measurement Whether the circuit measures qubits intermediately during execution.
//  * @param measure_all_at_the_end Whether the circuit should measure all qubits at the end.
//  * @param overwrite_file Whether the file should be overwritten if it already exists.
//  */
//  static void createRandomStabilizerCircuit(
//         const std::string &circuit_filename,
//         uint n_qubits,
//         uint depth,
//         uint gate_seed = 0,
//         uint qubit_seed = 0,
//         bool allow_intermediate_measurement = false,
//         bool measure_all_at_the_end = true,
//         bool overwrite_file = false
//  );
TEST(StabilizerCircuitTest, GenerateRandomCircuit4) {
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_4.qasm",
            25,
            500,
            0,
            0,
            false,
            true,
            true
    );
}

TEST(StabilizerCircuitTest, GenerateRandomCircuit5) {
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_5.qasm",
            50,
            1000,
            0,
            0,
            false,
            true,
            true
    );
}

TEST(StabilizerCircuitTest, GenerateRandomCircuit6) {
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_6.qasm",
            100,
            2500,
            0,
            0,
            false,
            true,
            true
    );
}

TEST(StabilizerCircuitTest, GenerateRandomCircuit7) {
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_7.qasm",
            25,
            500,
            10,
            10,
            true,
            false,
            true
    );
}

TEST(StabilizerCircuitTest, GenerateRandomCircuit8) {
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_8.qasm",
            50,
            1000,
            10,
            10,
            true,
            false,
            true
    );
}

TEST(StabilizerCircuitTest, GenerateRandomCircuit9) {
    StabilizerCircuit::createRandomStabilizerCircuit(
            "random_circuit_9.qasm",
            100,
            2500,
            10,
            10,
            true,
            false,
            true
    );
}

