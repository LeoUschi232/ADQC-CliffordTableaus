
#include "stabilizer_circuit.h"


namespace CliffordTableaus {
    std::string StabilizerCircuit::executeCircuit(const std::string &circuit_filename, StabilizerTableau &tableau) {
        auto file = retrieveCircuitFile(circuit_filename);

        std::string line;
        if (!std::getline(file, line) || line != "OPENQASM 3;") {
            throw std::runtime_error("Invalid QASM format: missing 'OPENQASM 3;' on the first line.");
        }

        // Read the second line (qreg q[n];) and parse the number of qubits
        if (!std::getline(file, line)) {
            throw std::runtime_error("Invalid QASM format: missing 'qreg q[n];' on the second line.");
        }

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
            // std::cout << line << std::endl;
            if (!applyGateLine(line, tableau, measurement_result)) {
                throw std::invalid_argument("Error! Expected file in QASM3 format.");
            }
        }
        return measurement_result;
    }


    std::string StabilizerCircuit::interactiveMode(StabilizerTableau &tableau) {
        uint n = 0;
        std::smatch match;
        while (true) {
            std::cout << "Initialize the number of qubit register in QASM3 format: qreg q[n];\n> ";
            std::string line;
            if (!std::getline(std::cin, line)) {
                // End input, just return empty
                return "";
            }
            trimLine(line);

            if (std::regex_match(line, match, qreg_regex)) {
                n = std::stoul(match[1]);
                break;
            } else {
                std::cout << "Error: Incorrect format. Expected format: qreg q[n];" << std::endl;
            }
        }

        tableau.initializeTableau(n);
        std::string measurement_result(n, 'x');
        std::cout << "Initialized circuit with " << n << " qubits.\n"
                  << "Available commands:\n"
                  << "Gates CNOT, H, S, Measure, X, Y, Z and SWAP applied to qubits in QASM3 format.\n"
                  << "exit|quit => Terminate interactive mode and print current measurement string.\n"
                  << "finish|measure all => Measure all remaining qubits and print the measurement string.\n";

        std::string line;
        while (true) {
            std::cout << "> ";
            if (!std::getline(std::cin, line)) {
                // End of input
                break;
            }
            trimLine(line);

            if (line.empty()) {
                continue;
            }
            if (line == "exit" || line == "quit") {
                break;
            }
            if (line == "finish" || line == "measure all") {
                for (uint q_index = 0; q_index < n; ++q_index) {
                    if (measurement_result.at(q_index) == 'x') {
                        uint8_t measurement = tableau.Measurement(q_index + 1);
                        measurement_result.at(q_index) = static_cast<char>('0' + measurement);
                    }
                }
                break;
            }

            if (!applyGateLine(line, tableau, measurement_result)) {
                std::cout << "Error: Invalid input." << std::endl;
            }
        }
        return measurement_result;
    }

    bool StabilizerCircuit::applyGateLine(
            const std::string &line, StabilizerTableau &tableau, std::string &measurement_result
    ) {
        std::smatch match;
        if (std::regex_match(line, match, id_regex)) {
            uint q_index = std::stoul(match[1]);

            // Measurement result is not affected by the identity gate
            tableau.Identity(q_index + 1);

            return true;
        } else if (std::regex_match(line, match, cnot_regex)) {
            uint control = std::stoul(match[1]);
            uint target = std::stoul(match[2]);

            tableau.CNOT(control + 1, target + 1);
            measurement_result.at(control) = 'x';
            measurement_result.at(target) = 'x';

            return true;
        } else if (std::regex_match(line, match, h_regex)) {
            uint q_index = std::stoul(match[1]);

            tableau.Hadamard(q_index + 1);
            measurement_result.at(q_index) = 'x';

            return true;
        } else if (std::regex_match(line, match, s_regex)) {
            uint q_index = std::stoul(match[1]);

            tableau.Phase(q_index + 1);
            measurement_result.at(q_index) = 'x';

            return true;
        } else if (std::regex_match(line, match, measure_regex)) {
            uint q_index = std::stoul(match[1]);

            uint8_t measurement = tableau.Measurement(q_index + 1);
            measurement_result.at(q_index) = static_cast<char>('0' + measurement);

            return true;
        } else if (std::regex_match(line, match, x_regex)) {
            uint q_index = std::stoul(match[1].str());

            tableau.PauliX(q_index + 1);
            measurement_result.at(q_index) = 'x';

            return true;
        } else if (std::regex_match(line, match, y_regex)) {
            uint q_index = std::stoul(match[1].str());

            tableau.PauliY(q_index + 1);
            measurement_result.at(q_index) = 'x';

            return true;
        } else if (std::regex_match(line, match, z_regex)) {
            uint q_index = std::stoul(match[1].str());

            tableau.PauliZ(q_index + 1);
            measurement_result.at(q_index) = 'x';

            return true;
        } else if (std::regex_match(line, match, swap_regex)) {
            uint q_index1 = std::stoul(match[1]);
            uint q_index2 = std::stoul(match[2]);

            tableau.SWAP(q_index1 + 1, q_index2 + 1);
            measurement_result.at(q_index1) = 'x';
            measurement_result.at(q_index2) = 'x';

            return true;
        } else {
            return false;
        }
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
        auto file = createCircuitFile(circuit_filename, overwrite_file);

        std::vector<Gate> allowed_gates = {PAULI_X, PAULI_Y, PAULI_Z, HADAMARD, PHASE};
        if (n_qubits >= 2) {
            allowed_gates.push_back(CNOT);
            allowed_gates.push_back(SWAP);
        }
        if (allow_intermediate_measurement) {
            allowed_gates.push_back(MEASURE);
        }

        std::mt19937 gate_generator(gate_seed);
        std::mt19937 qubit_generator(qubit_seed);
        std::discrete_distribution<int> gate_distribution;

        if (n_qubits >= 2 && allow_intermediate_measurement) {
            // 8 gates: X=0.13, Y=0.13, Z=0.13, CNOT=0.13, HADAMARD=0.13, PHASE=0.13, SWAP=0.13 MEASURE=0.09
            auto p1 = 0.13;
            auto p2 = 0.09;
            gate_distribution = std::discrete_distribution<int>({p1, p1, p1, p1, p1, p1, p1, p2});
        } else if (n_qubits >= 2) {
            // 7 gates: X=1/7, Y=1/7, Z=1/7, CNOT=1/7, HADAMARD=1/7, PHASE=1/7, SWAP=1/7
            auto p = 0.14285714285;
            gate_distribution = std::discrete_distribution<int>({p, p, p, p, p, p, p});
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
                case IDENTITY:
                    throw std::logic_error("Identity gate should not be selected.");
                case PAULI_X:
                    file << getPauliX(q1);
                    break;
                case PAULI_Y:
                    file << getPauliY(q1);
                    break;
                case PAULI_Z:
                    file << getPauliZ(q1);
                    break;
                case CNOT:
                    q2 = qubit_dist(qubit_generator);
                    while (q2 == q1) {
                        q2 = qubit_dist(qubit_generator);
                    }
                    file << getCNOT(q1, q2);
                    break;
                case HADAMARD:
                    file << getHadamard(q1);
                    break;
                case PHASE:
                    file << getPhase(q1);
                    break;
                case MEASURE:
                    file << getMeasurement(q1);
                    break;
                case SWAP:
                    q2 = qubit_dist(qubit_generator);
                    while (q2 == q1) {
                        q2 = qubit_dist(qubit_generator);
                    }
                    file << getSWAP(q1, q2);
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
        auto file = createCircuitFile(circuit_filename, overwrite_file);

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
                if (!std::regex_match(line, qreg_regex)) {
                    throw std::invalid_argument("The format is wrong.");
                }
                file << line << "\n";
                continue;
            }

            std::smatch match;
            if (std::regex_match(line, id_regex) ||
                std::regex_match(line, cnot_regex) ||
                std::regex_match(line, h_regex) ||
                std::regex_match(line, s_regex) ||
                std::regex_match(line, x_regex) ||
                std::regex_match(line, y_regex) ||
                std::regex_match(line, z_regex) ||
                std::regex_match(line, measure_regex) ||
                std::regex_match(line, swap_regex)
                    ) {
                file << line << "\n";
            } else {
                // Check if line starts with a known gate token,
                // if not, it's unsupported or format is wrong.
                if (line.rfind("id", 0) == 0 ||
                    line.rfind("cx", 0) == 0 ||
                    line.rfind('h', 0) == 0 ||
                    line.rfind('s', 0) == 0 ||
                    line.rfind("measure", 0) == 0 ||
                    line.rfind('x', 0) == 0 ||
                    line.rfind('y', 0) == 0 ||
                    line.rfind('z', 0) == 0 ||
                    line.rfind("swap", 0) == 0) {
                    throw std::invalid_argument("Gate not supported.");
                } else {
                    throw std::invalid_argument("Format wrong");
                }
            }
        }
    }

    std::ofstream StabilizerCircuit::createCircuitFile(const std::string &circuit_filename, bool overwrite_file) {
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

    std::ifstream StabilizerCircuit::retrieveCircuitFile(const std::string &circuit_filename) {
        // Get the directory of the current source file otherwise execution from different location will throw errors.
        // Ensure the directory exists by creating it if it doesn't.
        namespace fs = std::filesystem;
        fs::path base_directory = fs::path(__FILE__).parent_path() / "stabilizer_circuits";
        fs::create_directories(base_directory);
        fs::path file_path = base_directory / circuit_filename;

        // Check if the file exists. If it doesn't, throw an error.
        if (!fs::exists(file_path)) {
            throw std::runtime_error("File does not exist: " + file_path.string());
        }

        // Open the file for reading.
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file for reading: " + file_path.string());
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

    std::string StabilizerCircuit::getIdentity(uint qubit) {
        std::ostringstream builder;
        builder << "id q[" << qubit << "];\n";
        return builder.str();
    }

    std::string StabilizerCircuit::getPauliX(uint qubit) {
        std::ostringstream builder;
        builder << "x q[" << qubit << "];\n";
        return builder.str();
    }

    std::string StabilizerCircuit::getPauliY(uint qubit) {
        std::ostringstream builder;
        builder << "y q[" << qubit << "];\n";
        return builder.str();
    }

    std::string StabilizerCircuit::getPauliZ(uint qubit) {
        std::ostringstream builder;
        builder << "z q[" << qubit << "];\n";
        return builder.str();
    }

    std::string StabilizerCircuit::getSWAP(uint qubit1, uint qubit2) {
        std::ostringstream builder;
        builder << "swap q[" << qubit1 << "],q[" << qubit2 << "];\n";
        return builder.str();
    }
}
