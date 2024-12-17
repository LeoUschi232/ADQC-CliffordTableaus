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

        static void createRandomStabilizerCircuit(
                const std::string &circuit_filename,
                uint n_qubits,
                uint depth,
                uint gate_seed = 0,
                uint qubit_seed = 0,
                bool allow_intermediate_measurement = false,
                bool measure_all_at_the_end = true
        );

        static void writeStabilizerCircuitToFile(const std::string &p_circuit_filename, const std::string &circuit);
    };

    enum Gate {
        CNOT,
        HADAMARD,
        PHASE,
        MEASURE
    };
}