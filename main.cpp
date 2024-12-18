#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <getopt.h>
#include "stabilizer_circuit.h"
#include "stabilizer_tableau.h"
#include "improved_stabilizer_tableau.h"

using namespace CliffordTableaus;

void print_help(const char *program_name) {
    std::cout << "Usage: " << program_name << " [OPTIONS]\n"
              << "OPTIONS:\n"
              << "  -i, --input <input_filename>       Input file containing the circuit in QASM3 format.\n"
              << "  -s, --stabilizer <stabilizer-id>   Stabilizer algorithm ID (default: 1).\n"
              << "  -o, --output <output_filename>     Output file for measurement results.\n"
              << "  -n, --num-shots <num-shots>        Number of shots to execute (default: 1).\n"
              << "  -h, --help                         Display this help message and exit.\n";
}

int main(int argc, char *argv[]) {
    std::string input_filename;
    std::string output_filename;

    // Default to ImprovedStabilizerTableau
    unsigned int stabilizer_id = 1;
    unsigned int num_shots = 1;

    // Define options
    struct option long_options[] = {
            {"input",      required_argument, nullptr, 'i'},
            {"stabilizer", required_argument, nullptr, 's'},
            {"output",     required_argument, nullptr, 'o'},
            {"num-shots",  required_argument, nullptr, 'n'},
            {"help",       no_argument,       nullptr, 'h'},
            {nullptr, 0,                      nullptr, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "i:s:o:n:h", long_options, nullptr)) != -1) {
        switch (opt) {
            case 'i':
                input_filename = optarg;
                break;
            case 's':
                stabilizer_id = std::stoul(optarg);
                break;
            case 'o':
                output_filename = optarg;
                break;
            case 'n':
                num_shots = std::stoul(optarg);
                break;
            case 'h':
                print_help(argv[0]);
                return 0;
            default:
                std::cerr << "Invalid option. Use -h or --help for usage information." << std::endl;
                return 1;
        }
    }

    // Select stabilizer tableau
    std::unique_ptr<StabilizerTableau> stabilizerTableau;
    // NOLINTNEXTLINE
    switch (stabilizer_id) {
        case 1:
            stabilizerTableau = std::make_unique<ImprovedStabilizerTableau>();
            break;
        default:
            std::cerr << "Error: Unsupported stabilizer algorithm ID: " << stabilizer_id << std::endl;
            return 1;
    }

    try {
        if (input_filename.empty()) {
            // Interactive mode
            std::string result = StabilizerCircuit::interactiveMode(*stabilizerTableau);
            std::cout << "Final measurement: " << result << std::endl;
        } else {
            // Read circuit from file
            std::unordered_map<std::string, unsigned int> measurement_results;
            for (unsigned int shot = 0; shot < num_shots; ++shot) {
                std::string measurement = StabilizerCircuit::executeCircuit(input_filename, *stabilizerTableau);
                ++measurement_results[measurement];
            }

            // Sort and output results
            std::vector<std::pair<std::string, unsigned int>> sorted_results(
                    measurement_results.begin(), measurement_results.end()
            );
            std::sort(sorted_results.begin(), sorted_results.end());

            std::ostringstream output;
            output << "{";
            for (size_t i = 0; i < sorted_results.size(); ++i) {
                output << "\"" << sorted_results[i].first << "\": " << sorted_results[i].second;
                if (i < sorted_results.size() - 1) {
                    output << ", ";
                }
            }
            output << "}";

            // Print to console
            std::cout << "Measurement results: " << output.str() << std::endl;

            // Write to file if output filename is provided
            if (!output_filename.empty()) {
                std::ofstream out_file(output_filename);
                if (!out_file) {
                    std::cerr << "Error: Unable to write to file: " << output_filename << std::endl;
                    return 1;
                }
                out_file << output.str();
                out_file.close();
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
