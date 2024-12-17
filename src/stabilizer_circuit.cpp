#include "stabilizer_circuit.h"

namespace CliffordTableaus {
    StabilizerCircuit::StabilizerCircuit(const std::string &circuit_filename) : circuit_filename(circuit_filename) {
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
