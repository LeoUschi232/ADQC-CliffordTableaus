#include "stabilizer_circuit.h"


namespace CliffordTableaus {
    StabilizerCircuit::StabilizerCircuit(std::string circuit_filename) : n(0),
                                                                         circuit_filename(std::move(circuit_filename)) {
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


    void StabilizerCircuit::createRandomStabilizerCircuit(
            const std::string &circuit_filename,
            uint n_qubits,
            uint depth,
            uint gate_seed,
            uint qubit_seed,
            bool allow_intermediate_measurement,
            bool measure_all_at_the_end
    ) {
        std::vector<Gate> allowed_gates = {Gate::CNOT, Gate::HADAMARD, Gate::PHASE};
        if (allow_intermediate_measurement) {
            allowed_gates.push_back(Gate::MEASURE);
        }

        std::mt19937 gate_generator(gate_seed);
        std::mt19937 qubit_generator(qubit_seed);
        std::discrete_distribution<int> gate_distribution;

        if (allow_intermediate_measurement) {
            // 4 gates: CNOT=3/10, HADAMARD=3/10, PHASE=3/10, MEASURE=1/10
            gate_distribution = std::discrete_distribution<int>({0.3, 0.3, 0.3, 0.1});
        } else {
            // 3 gates: CNOT=1/3, HADAMARD=1/3, PHASE=1/3
            auto probability = 1.0 / 3.0;
            gate_distribution = std::discrete_distribution<int>({probability, probability, probability});
        }
        std::uniform_int_distribution<uint> qubit_dist(0, n_qubits - 1);

        std::ofstream file("stabilizer_circuits/" + circuit_filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file for writing.");
        }

        file << "OPENQASM 3;\n";
        file << "qreg q[" << n_qubits << "];\n";
        for (int i = 0; i < depth; ++i) {
            int gate_index = gate_distribution(gate_generator);
            Gate g = allowed_gates[gate_index];

            if (g == Gate::CNOT) {
                uint q1 = qubit_dist(qubit_generator);
                uint q2 = qubit_dist(qubit_generator);
                while (q2 == q1) {
                    q2 = qubit_dist(qubit_generator);
                }
                file << "cx q[" << q1 << "],q[" << q2 << "];\n";
            } else if (g == Gate::HADAMARD) {
                uint q1 = qubit_dist(qubit_generator);
                file << "h q[" << q1 << "];\n";
            } else if (g == Gate::PHASE) {
                uint q1 = qubit_dist(qubit_generator);
                file << "s q[" << q1 << "];\n";
            } else if (g == Gate::MEASURE) {
                uint q1 = qubit_dist(qubit_generator);
                file << "measure q[" << q1 << "];\n";
            }
        }

        if (measure_all_at_the_end) {
            for (uint qubit = 0; qubit < n_qubits; ++qubit) {
                file << "measure q[" << qubit << "];\n";
            }
        }
    }


    void StabilizerCircuit::writeStabilizerCircuitToFile(
            const std::string &circuit_filename,
            const std::string &circuit
    ) {
        {
            std::ifstream test_file("stabilizer_circuits/" + circuit_filename);
            if (test_file.good()) {
                throw std::invalid_argument("File already exists");
            }
        }

        std::ofstream file("stabilizer_circuits/" + circuit_filename, std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to create file.");
        }

        std::istringstream iss(circuit);
        std::string line;
        int line_number = 0;
        while (std::getline(iss, line)) {
            line_number++;

            // These two lines only remove leading and trailing whitespace from the entire line,
            // not the whitespace between words or tokens.
            // They use std::find_if to find the first and last non-whitespace characters.
            // All internal spacing, such as the space between "h" and "q[0];", remains intact.
            line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char c) {
                return !std::isspace(c);
            }));
            line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char c) {
                return !std::isspace(c);
            }).base(), line.end());

            if (line_number == 1) {
                if (line != "OPENQASM 3;") {
                    throw std::invalid_argument("The format is wrong");
                }
                file << line << "\n";
                continue;
            }

            if (line_number == 2) {
                std::regex qreg_regex(R"(^qreg q\[(\d+)\];$)");
                if (!std::regex_match(line, qreg_regex)) {
                    throw std::invalid_argument("The format is wrong.");
                }
                file << line << "\n";
                continue;
            }

            // From the third line on, we expect gate instructions
            // Supported gates and their patterns:
            // cx q[i],q[j];
            // h q[i];
            // s q[i];
            // measure q[i];
            std::regex cnot_regex(R"(^cx q\[(\d+)\],q\[(\d+)\];$)");
            std::regex h_regex(R"(^h q\[(\d+)\];$)");
            std::regex s_regex(R"(^s q\[(\d+)\];$)");
            std::regex measure_regex(R"(^measure q\[(\d+)\];$)");

            if (std::regex_match(line, cnot_regex) ||
                std::regex_match(line, h_regex) ||
                std::regex_match(line, s_regex) ||
                std::regex_match(line, measure_regex)) {
                file << line << "\n";
            } else {
                // Check if line starts with a known gate token,
                // if not, it's unsupported or format is wrong.
                if (line.rfind("cx", 0) == 0 ||
                    line.rfind('h', 0) == 0 ||
                    line.rfind('s', 0) == 0 ||
                    line.rfind("measure", 0) == 0) {
                    throw std::invalid_argument("Gate not supported.");
                } else {
                    throw std::invalid_argument("Format wrong");
                }
            }
        }
    }


}
