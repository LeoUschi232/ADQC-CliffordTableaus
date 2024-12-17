#pragma once

#include <cstdint>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <regex>
#include <utility>
#include <random>
#include <complex>
#include <filesystem>

namespace CliffordTableaus {
    using uint = std::size_t;

    class StabilizerCircuit {
    private:
        /**
         * The number of qubits in the system.
         */
        uint n;

        /**
         * Name of the file containing the circuit that would currently be executed.
         */
        std::string circuit_filename;

        /**
         * Initialize the circuit from the file.
         * This method sets the number of qubits in the system to the the number of qubits provided by the circuit.
         */
        void initializeCircuit();

        /**
         * Retrieve the file containing the circuit.
         * @param circuit_filename File containing the circuit in QASM3 format.
         * @param overwrite_file Whether the file should be overwritten if it already exists.
         * @return An output file stream to the circuit file.
         */
        static std::ofstream retrieveCircuitFile(const std::string &circuit_filename, bool overwrite_file);

    public:
        /**
         * Construct a new StabilizerCircuit object.
         * The qubits are initialized to the state |0〉^(⊗n) and the circuit is empty.
         * @param n Number of qubits in the system.
         */
        explicit StabilizerCircuit(uint n) : n(n) {}


        /**
         * Construct a new StabilizerCircuit object from a file.
         * The file contains the circuit in QASM3 format, and the number of qubits is inferred.
         * @param circuit_filename Path to the file containing the circuit.
         */
        explicit StabilizerCircuit(std::string circuit_filename);

        /**
         * Set the circuit_filename from a file.
         * Also initializes the number of qubits.
         * @param p_circuit_filename File containing the circuit in QASM3 format.
         */
        void setCircuit(const std::string &p_circuit_filename);

        /**
         * Create a random stabilizer circuit and write it to a file.
         * @param circuit_filename Name of the file to write the circuit to.
         * @param n_qubits Number of qubits in the system.
         * @param depth Number of gates in the circuit.
         * @param gate_seed Seed for the random number generator for selecting gates.
         * @param qubit_seed Seed for the random number generator for selecting qubits.
         * @param allow_intermediate_measurement Whether the circuit measures qubits intermediately during execution.
         * @param measure_all_at_the_end Whether the circuit should measure all qubits at the end.
         * @param overwrite_file Whether the file should be overwritten if it already exists.
         */
        static void createRandomStabilizerCircuit(
                const std::string &circuit_filename,
                uint n_qubits,
                uint depth,
                uint gate_seed = 0,
                uint qubit_seed = 0,
                bool allow_intermediate_measurement = false,
                bool measure_all_at_the_end = true,
                bool overwrite_file = false
        );

        /**
         * Write a stabilizer circuit to a file.
         * @param circuit_filename Name of the file to write the circuit to.
         * @param circuit Stabilizer circuit in QASM3 format.
         * @param overwrite_file Whether the file should be overwritten if it already exists.
         */
        static void writeStabilizerCircuitToFile(
                const std::string &circuit_filename,
                const std::string &circuit,
                bool overwrite_file
        );

        static std::string getCNOT(uint qubit1, uint qubit2);

        static std::string getHadamard(uint qubit);

        static std::string getPhase(uint qubit);

        static std::string getMeasurement(uint qubit);

        static std::string decomposePauliX(uint qubit);

        static std::string decomposePauliY(uint qubit);

        static std::string decomposePauliZ(uint qubit);
    };

    enum Gate {
        PAULI_X,
        PAULI_Y,
        PAULI_Z,
        CNOT,
        HADAMARD,
        PHASE,
        MEASURE
    };
}