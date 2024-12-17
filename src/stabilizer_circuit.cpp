#include "stabilizer_circuit.h"


namespace CliffordTableaus {
    std::string StabilizerCircuit::executeCircuit(const std::string &circuit_filename, StabilizerTableau &tableau) {
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

        auto n = std::stoul(match[1]);
        tableau.initializeTableau(n);
        std::string measurement_result(n, 'x');

        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            // The +1 are necessary because the qubits are 0-indexed in QASM but 1-indexed in the tableau.
            if (std::regex_match(line, match, cnot_regex)) {
                uint control = std::stoul(match[1]) + 1;
                uint target = std::stoul(match[2]) + 1;
                tableau.CNOT(control, target);
                measurement_result.at(control) = 'x';
                measurement_result.at(target) = 'x';
            } else if (std::regex_match(line, match, h_regex)) {
                uint q_index = std::stoul(match[1].str()) + 1;
                tableau.Hadamard(q_index);
                measurement_result.at(q_index) = 'x';
            } else if (std::regex_match(line, match, s_regex)) {
                uint q_index = std::stoul(match[1].str()) + 1;
                tableau.Phase(q_index);
                measurement_result.at(q_index) = 'x';
            } else if (std::regex_match(line, match, measure_regex)) {
                uint q_index = std::stoul(match[1].str()) + 1;
                uint8_t measurement = tableau.Measurement(q_index);
                measurement_result.at(q_index) = static_cast<char>('0' + measurement);
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
        return measurement_result;
    }


    void StabilizerCircuit::createRandomStabilizerCircuit(
            const std::string &circuit_filename,
            uint n_qubits,
            uint depth,
            uint gate_seed,
            uint qubit_seed,
            bool allow_intermediate_measurement,
            bool measure_all_at_the_end,
            bool overwrite_file
    ) {
        auto file = retrieveCircuitFile(circuit_filename, overwrite_file);

        std::vector<Gate> allowed_gates = {Gate::PAULI_X, Gate::PAULI_Y, Gate::PAULI_Z, Gate::HADAMARD, Gate::PHASE};
        if (n_qubits >= 2) {
            allowed_gates.push_back(Gate::CNOT);
        }
        if (allow_intermediate_measurement) {
            allowed_gates.push_back(Gate::MEASURE);
        }

        std::mt19937 gate_generator(gate_seed);
        std::mt19937 qubit_generator(qubit_seed);
        std::discrete_distribution<int> gate_distribution;

        if (n_qubits >= 2 && allow_intermediate_measurement) {
            // 7 gates: X=0.16, Y=0.16, Z=0.16, CNOT=0.16, HADAMARD=0.16, PHASE=0.16, MEASURE=0.04
            auto p1 = 0.16;
            auto p2 = 0.04;
            gate_distribution = std::discrete_distribution<int>({p1, p1, p1, p1, p1, p1, p2});
        } else if (n_qubits >= 2) {
            // 6 gates: X=1/6, Y=1/6, Z=1/6, CNOT=1/6, HADAMARD=1/6, PHASE=1/6
            auto p = 1.0 / 6.0;
            gate_distribution = std::discrete_distribution<int>({p, p, p, p, p, p});
        } else if (allow_intermediate_measurement) {
            // 6 gates: X=0.19, Y=0.19, Z=0.19, HADAMARD=0.19, PHASE=0.19, MEASURE=0.05
            auto p1 = 0.19;
            auto p2 = 0.05;
            gate_distribution = std::discrete_distribution<int>({p1, p1, p1, p1, p1, p1, p2});
        } else {
            // 5 gates: X=1/5, Y=1/5, Z=1/5, HADAMARD=1/5, PHASE=1/5
            auto p = 0.2;
            gate_distribution = std::discrete_distribution<int>({p, p, p});
        }
        std::uniform_int_distribution<uint> qubit_dist(0, n_qubits - 1);

        file << "OPENQASM 3;\n";
        file << "qreg q[" << n_qubits << "];\n";
        for (int i = 0; i < depth; ++i) {
            uint q1 = qubit_dist(qubit_generator);
            uint q2 = 0;

            switch (allowed_gates[gate_distribution(gate_generator)]) {
                case Gate::PAULI_X:
                    file << decomposePauliX(q1);
                    break;
                case Gate::PAULI_Y:
                    file << decomposePauliY(q1);
                    break;
                case Gate::PAULI_Z:
                    file << decomposePauliZ(q1);
                    break;
                case Gate::CNOT:
                    q2 = qubit_dist(qubit_generator);
                    while (q2 == q1) {
                        q2 = qubit_dist(qubit_generator);
                    }
                    file << getCNOT(q1, q2);
                    break;
                case Gate::HADAMARD:
                    file << getHadamard(q1);
                    break;
                case Gate::PHASE:
                    file << getPhase(q1);
                    break;
                case Gate::MEASURE:
                    file << getMeasurement(q1);
                    break;
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
            const std::string &circuit,
            bool overwrite_file
    ) {
        auto file = retrieveCircuitFile(circuit_filename, overwrite_file);

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

            std::smatch match;
            if (std::regex_match(line, cnot_regex) ||
                std::regex_match(line, h_regex) ||
                std::regex_match(line, s_regex) ||
                std::regex_match(line, measure_regex)) {
                file << line << "\n";
            } else if (std::regex_match(line, match, x_regex)) {
                uint q_index = std::stoul(match[1].str());
                file << decomposePauliX(q_index);
            } else if (std::regex_match(line, match, y_regex)) {
                uint q_index = std::stoul(match[1].str());
                file << decomposePauliY(q_index);
            } else if (std::regex_match(line, match, z_regex)) {
                uint q_index = std::stoul(match[1].str());
                file << decomposePauliZ(q_index);
            } else {
                // Check if line starts with a known gate token,
                // if not, it's unsupported or format is wrong.
                if (line.rfind("cx", 0) == 0 ||
                    line.rfind('h', 0) == 0 ||
                    line.rfind('s', 0) == 0 ||
                    line.rfind("measure", 0) == 0 ||
                    line.rfind('x', 0) == 0 ||
                    line.rfind('y', 0) == 0 ||
                    line.rfind('z', 0) == 0) {
                    throw std::invalid_argument("Gate not supported.");
                } else {
                    throw std::invalid_argument("Format wrong");
                }
            }
        }
    }

    std::ofstream StabilizerCircuit::retrieveCircuitFile(const std::string &circuit_filename, bool overwrite_file) {
        // Get the directory of the current source file otherwise execution from different location will throw errors.
        // Ensure the directory exists by creating it if it doesn't.
        // Finally construct the full path to the file.
        namespace fs = std::filesystem;
        fs::path base_directory = fs::path(__FILE__).parent_path() / "stabilizer_circuits";
        fs::create_directories(base_directory);
        fs::path file_path = base_directory / circuit_filename;

        // If overwrite_file is true empty it and start writing it anew.
        // If overwrite_file is false, check if the file exists and throw an error if it does.
        if (!overwrite_file && fs::exists(file_path)) {
            throw std::invalid_argument("File already exists.");
        }
        std::ofstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file for writing.");
        }
        return file;
    }


    std::string StabilizerCircuit::getCNOT(uint control, uint target) {
        std::ostringstream builder;
        builder << "cx q[" << control << "],q[" << target << "];\n";
        return builder.str();
    }

    std::string StabilizerCircuit::getHadamard(uint qubit) {
        std::ostringstream builder;
        builder << "h q[" << qubit << "];\n";
        return builder.str();
    }

    std::string StabilizerCircuit::getPhase(uint qubit) {
        std::ostringstream builder;
        builder << "s q[" << qubit << "];\n";
        return builder.str();
    }

    std::string StabilizerCircuit::getMeasurement(uint qubit) {
        std::ostringstream builder;
        builder << "measure q[" << qubit << "];\n";
        return builder.str();
    }


    std::string StabilizerCircuit::decomposePauliX(uint qubit) {
        // Decomposition of the Pauli-X-Gate:
        // X=HZH=HSSH
        std::ostringstream builder;
        builder << "h q[" << qubit << "];\n"
                << "s q[" << qubit << "];\n"
                << "s q[" << qubit << "];\n"
                << "h q[" << qubit << "];\n";
        return builder.str();

    }

    std::string StabilizerCircuit::decomposePauliY(uint qubit) {
        // Decomposition of the Pauli-Y-Gate:
        // iY=ZX=SSHSSH
        std::ostringstream builder;
        builder << "s q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";
        builder << "h q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";
        builder << "h q[" << qubit << "];\n";

        // Now, the preceding factor i has to be removed by multiplying -i to the superposition of states.
        // First, apply -i to the |1〉 state.
        builder << "s q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";

        // Second, flip the states using a decomposed X-gate,
        // and apply -i to the new |1〉, which is the old |0〉.
        builder << "h q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";
        builder << "h q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";

        // Third, flip the states back to recover the original state,
        // now with the i factor removed.
        builder << "h q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";
        builder << "s q[" << qubit << "];\n";
        builder << "h q[" << qubit << "];\n";
        return builder.str();
    }

    std::string StabilizerCircuit::decomposePauliZ(uint qubit) {
        // Decomposition of the Pauli-Z-Gate:
        // Z=SS
        std::ostringstream builder;
        builder << "s q[" << qubit << "];\n"
                << "s q[" << qubit << "];\n";
        return builder.str();
    }


}
