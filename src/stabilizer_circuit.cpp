#include "stabilizer_circuit.h"

#include <utility>

namespace CliffordTableaus {
    StabilizerCircuit::StabilizerCircuit(std::string circuit_filename) : n(0), circuit_filename(std::move(circuit_filename)) {
        initializeCircuit();
    }

    void StabilizerCircuit::setCircuit(const std::string &p_circuit_filename) {
        this->circuit_filename = p_circuit_filename;
        initializeCircuit();
    }

    void StabilizerCircuit::initializeCircuit() {
        std::ifstream file(circuit_filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open the circuit file.");
        }

        std::string line;
        if (!std::getline(file, line) || line != "OPENQASM 3;") {
            throw std::runtime_error("Invalid QASM format: missing 'OPENQASM 3;' on the first line.");
        }

        // Read the second line (qreg q[n];) and parse the number of qubits
        if (!std::getline(file, line)) {
            throw std::runtime_error("Invalid QASM format: missing 'qreg q[n];' on the second line.");
        }

        std::regex qreg_regex(R"(^qreg q\[(\d+)\];$)");
        std::smatch match;
        if (!std::regex_match(line, match, qreg_regex)) {
            throw std::runtime_error("Invalid QASM format: 'qreg q[n];' expected on the second line.");
        }

        n = std::stoul(match[1]);
    }


}
