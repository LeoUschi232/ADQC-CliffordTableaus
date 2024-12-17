#pragma once

#include <cstdint>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>

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
        explicit StabilizerCircuit(const std::string &circuit_filename);


    };


}