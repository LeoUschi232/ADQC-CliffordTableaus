#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <bitset>
#include <stdexcept>

class Quarray {
public:
    std::vector<std::vector<double>> matrix;

    Quarray(const std::vector<std::vector<double>> &input) {
        validate_input(input);
        matrix = input;
    }

    Quarray operator*(const Quarray &other) const {
        return kronecker_product(*this, other);
    }

    Quarray operator/(const Quarray &other) const {
        Quarray inv_other = inverse(other);
        return matrix_multiply(*this, inv_other);
    }

    friend std::ostream &operator<<(std::ostream &os, const Quarray &qa) {
        return qa.to_string(os);
    }

    static Quarray fix_matrix(const Quarray &input) {
        Quarray result = input;
        for (std::vector<double> &row: result.matrix) {
            for (double &val: row) {
                val = std::round(val * 1e12) / 1e12;  // Round to 12 decimals
            }
        }
        return result;
    }

    static std::vector<std::string> get_bitstrings(int length) {
        std::vector<std::string> bitstrings;
        for (int i = 0; i < (1 << length); ++i) {
            bitstrings.push_back(std::bitset<32>(i).to_string().substr(32 - length));
        }
        return bitstrings;
    }

    static std::vector<std::string> get_states(int length) {
        std::vector<std::string> states;
        for (const std::string &bitstring: get_bitstrings(length)) {
            states.push_back("|" + bitstring + "⟩");
        }
        return states;
    }

    static std::string binstring(int value, int length = 0) {
        std::string binary = std::bitset<32>(value).to_string();
        return binary.substr(32 - std::max(length, 0));
    }

private:
    static void validate_input(const std::vector<std::vector<double>> &input) {
        size_t rows = input.size();
        if (rows == 0 || (rows & (rows - 1)) != 0) {
            throw std::invalid_argument("Matrix must have dimensions that are powers of 2.");
        }
        for (const std::vector<double> &row: input) {
            if (row.size() != rows) {
                throw std::invalid_argument("Matrix must be square.");
            }
        }
    }

    static Quarray kronecker_product(const Quarray &a, const Quarray &b) {
        std::vector<std::vector<double>> result;
        size_t a_rows = a.matrix.size();
        size_t b_rows = b.matrix.size();
        for (size_t i = 0; i < a_rows; ++i) {
            for (size_t j = 0; j < b_rows; ++j) {
                std::vector<double> row;
                for (size_t k = 0; k < a.matrix[i].size(); ++k) {
                    for (size_t l = 0; l < b.matrix[j].size(); ++l) {
                        row.push_back(a.matrix[i][k] * b.matrix[j][l]);
                    }
                }
                result.push_back(row);
            }
        }
        return Quarray(result);
    }

    static Quarray inverse(const Quarray &input) {
        // Simplified implementation for demonstration;
        // you'd need an actual matrix inversion algorithm.
        throw std::runtime_error("Matrix inversion not implemented.");
    }

    static Quarray matrix_multiply(const Quarray &a, const Quarray &b) {
        size_t n = a.matrix.size();
        std::vector<std::vector<double>> result(n, std::vector<double>(n, 0.0));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                for (size_t k = 0; k < n; ++k) {
                    result[i][j] += a.matrix[i][k] * b.matrix[k][j];
                }
            }
        }
        return Quarray(result);
    }

    std::ostream &to_string(std::ostream &os) const {
        for (const std::vector<double> &row: matrix) {
            os << "[";
            for (size_t i = 0; i < row.size(); ++i) {
                if (i > 0) os << ", ";
                os << std::setprecision(12) << row[i];
            }
            os << "]\n";
        }
        return os;
    }
};
