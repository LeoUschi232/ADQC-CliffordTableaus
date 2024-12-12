#include "qutils.h"


namespace CliffordTableaus {
    static bool isclose(double a, double b, double rel_tol = 1e-12, double abs_tol = 0.0) {
        return std::fabs(a - b) <= std::max(rel_tol * std::max(std::fabs(a), std::fabs(b)), abs_tol);
    }

    std::vector<std::string> get_bitstrings(int length) {
        std::vector<std::string> bitstrings;
        int total = static_cast<int>(std::pow(2, length));
        for (int i = 0; i < total; ++i) {
            std::ostringstream bitstring;
            for (int j = length - 1; j >= 0; --j) {
                bitstring << ((i >> j) & 1);
            }
            bitstrings.push_back(bitstring.str());
        }
        return bitstrings;
    }

    std::vector<std::string> get_states(int length) {
        std::vector<std::string> states;
        std::vector<std::string> bitstrings = get_bitstrings(length);
        for (const auto &bitstring: bitstrings) {
            states.push_back("|" + bitstring + "⟩");
        }
        return states;
    }
}