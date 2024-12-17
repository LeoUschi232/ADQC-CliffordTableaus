#pragma once

#include "stabilizer_tableau.h"

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
         * Retrieve the file containing the circuit.
         * @param circuit_filename File containing the circuit in QASM3 format.
         * @param overwrite_file Whether the file should be overwritten if it already exists.
         * @return An output file stream to the circuit file.
         */
        static std::ofstream retrieveCircuitFile(const std::string &circuit_filename, bool overwrite_file);


    public:
        /**
         * Execute a stabilizer circuit given by the QASM3 code in the file given by circuit_filename
         * using the provided stabilizer tableau.
         * If qubits are measured without further operations, the returned string will contain the measurement results.
         * In place of all unmeasured qubits, the return string will contain 'x'.
         * @param circuit_filename File containing the circuit in QASM3 format.
         * @param tableau Stabilizer tableau to use to execute the circuit.
         * @return The final measurement of the executed circuit
         * using '0' and '1' for measured qubits and 'x' for unmeasured qubits.
         */
        static std::string executeCircuit(const std::string &circuit_filename,  StabilizerTableau &tableau );


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

        /**
         * Get the string of a line of QASM3 code which applies the CNOT gate
         * to target qubit depending on the control qubit.
         * @param control Control qubit.
         * @param target Target qubit to apply the X-gate to if the control qubit is |1〉.
         * @return Line of QASM3 code corresponding to the application of the CNOT gate
         * with the given control and target qubits.
         */
        static std::string getCNOT(uint control, uint target);

        /**
         * Get the string of a line of QASM3 code which applies the Hadamard gate to the qubit.
         * @param qubit Qubit to apply the Hadamard gate to.
         * @return Line of QASM3 code corresponding to the application of the Hadamard gate to the qubit.
         */
        static std::string getHadamard(uint qubit);

        /**
         * Get the string of a line of QASM3 code which applies the Phase gate to the qubit.
         * @param qubit Qubit to apply the Phase gate to.
         * @return Line of QASM3 code corresponding to the application of the Phase gate to the qubit.
         */
        static std::string getPhase(uint qubit);

        /**
         * Get the string of a line of QASM3 code which measures the qubit.
         * @param qubit Qubit to measure.
         * @return Line of QASM3 code corresponding to the measurement of the qubit.
         */
        static std::string getMeasurement(uint qubit);

        /**
         * Decompose the Pauli-X gate into a sequence of CNOt, Hadamard, and Phase gates.
         * @param qubit Qubit to apply the Pauli-X gate to.
         * @return Lines of QASM3 code corresponding to the decomposition of the Pauli-X gate.
         */
        static std::string decomposePauliX(uint qubit);

        /**
         * Decompose the Pauli-Y gate into a sequence of CNOt, Hadamard, and Phase gates.
         * @param qubit Qubit to apply the Pauli-Y gate to.
         * @return Lines of QASM3 code corresponding to the decomposition of the Pauli-Y gate.
         */
        static std::string decomposePauliY(uint qubit);

        /**
         * Decompose the Pauli-Z gate into a sequence of CNOt, Hadamard, and Phase gates.
         * @param qubit Qubit to apply the Pauli-Z gate to.
         * @return Lines of QASM3 code corresponding to the decomposition of the Pauli-Z gate.
         */
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