#pragma once

#include "stabilizer_tableau.h"

#include <iostream>
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
    static const std::regex qreg_regex = std::regex(R"(^qreg q\[(\d+)\];$)");
    static const std::regex id_regex = std::regex(R"(^id q\[(\d+)\];$)");
    static const std::regex cnot_regex = std::regex(R"(^cx q\[(\d+)\],q\[(\d+)\];$)");
    static const std::regex h_regex = std::regex(R"(^h q\[(\d+)\];$)");
    static const std::regex s_regex = std::regex(R"(^s q\[(\d+)\];$)");
    static const std::regex x_regex = std::regex(R"(^x q\[(\d+)\];$)");
    static const std::regex y_regex = std::regex(R"(^y q\[(\d+)\];$)");
    static const std::regex z_regex = std::regex(R"(^z q\[(\d+)\];$)");
    static const std::regex swap_regex = std::regex(R"(^swap q\[(\d+)\],q\[(\d+)\];$)");
    static const std::regex measure_regex = std::regex(R"(^measure q\[(\d+)\];$)");

    class StabilizerCircuit {
    private:
        /**
         * Create the file containing the circuit.
         * @param circuit_filename File containing the circuit in QASM3 format.
         * @param overwrite_file Whether the file should be overwritten if it already exists.
         * @return An output file stream to the circuit file.
         */
        static std::ofstream createCircuitFile(const std::string &circuit_filename, bool overwrite_file);

        /**
         * Retrieve the file containing the circuit.
         * @param circuit_filename File containing the circuit in QASM3 format.
         * @return A file stream to the circuit file.
         */
        static std::ifstream retrieveCircuitFile(const std::string &circuit_filename);

        /**
         * Apply the operation given by the line, which is expected to be in QASM3 syntax to the tableau.
         * In case the operation has an effect on the measurement results, update the measurement result string.
         * @param line Line in QASM3 syntax which describes the operation to perform.
         * @param tableau Utilized Tableau to apply the operation to.
         * @param measurement_result String with running measurement results.
         * @return Whether the operation was successfully applied.
         */
        static bool applyGateLine(const std::string &line, StabilizerTableau &tableau, std::string &measurement_result);

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
        static std::string executeCircuit(const std::string &circuit_filename, StabilizerTableau &tableau);

        /**
         * Launch the interactive mode for executing stabilizer circuits.
         * The interactive mode allows the user to dynamically and consecutively apply gates to the stabilizer tableau.
         * Supported gates are Pauli-X, Pauli-Y, Pauli-Z, CNOT, Hadamard, Phase, and Measurement.
         * Commands must be provided in the QASM3 syntax.
         * All commands not in QASM3 syntax will default to NO-OP.
         * Use "exit" or "quit" to exit the interactive mode and output the measurement results.
         * Use "finish" or "measure all" to measure all remaining qubits and output the measurement results.
         * @param tableau Stabilizer tableau to use for the interactive mode.
         */
        static std::string interactiveMode(StabilizerTableau &tableau);

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
         * Get the string of a line of QASM3 code which applies the identity gate to the qubit.
         * @param qubit Qubit to apply the identity gate to.
         * @return Line of QASM3 code corresponding to the application of the identity gate to the qubit.
         */
        static std::string getIdentity(uint qubit);

        /**
         * Get the string of a line of QASM3 code which applies the Pauli-X gate to the qubit.
         * @param qubit Qubit to apply the Pauli-X gate to.
         * @return Line of QASM3 code corresponding to the application of the Pauli-X gate to the qubit.
         */
        static std::string getPauliX(uint qubit);

        /**
         * Get the string of a line of QASM3 code which applies the Pauli-Y gate to the qubit.
         * @param qubit Qubit to apply the Pauli-Y gate to.
         * @return Line of QASM3 code corresponding to the application of the Pauli-Y gate to the qubit.
         */
        static std::string getPauliY(uint qubit);

        /**
         * Get the string of a line of QASM3 code which applies the Pauli-Z gate to the qubit.
         * @param qubit Qubit to apply the Pauli-Z gate to.
         * @return Line of QASM3 code corresponding to the application of the Pauli-Z gate to the qubit.
         */
        static std::string getPauliZ(uint qubit);

        /**
         * Get the string of a line of QASM3 code which applies the SWAP gate to the qubits.
         * @param qubit1 Qubit to swap with qubit2.
         * @param qubit2 Qubit to swap with qubit1.
         * @return Line of QASM3 code corresponding to the application of the SWAP gate to the qubits.
         */
        static std::string getSWAP(uint qubit1, uint qubit2);
    };

    /**
     * Trim the line by removing leading and trailing whitespace.
     * @param line Line to trim the leading and trailing whitespace from.
     */
    static void trimLine(std::string &line) {
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char c) {
            return !std::isspace(c);
        }));
        line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char c) {
            return !std::isspace(c);
        }).base(), line.end());
    }

    /**
     * Supported gates in the stabilizer circuit.
     */
    enum Gate {
        IDENTITY,
        PAULI_X,
        PAULI_Y,
        PAULI_Z,
        CNOT,
        HADAMARD,
        PHASE,
        MEASURE,
        SWAP
    };
}