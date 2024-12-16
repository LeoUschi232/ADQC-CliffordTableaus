#include "quarray.h"

#include <algorithm>
#include <cmath>
#include <random>
#include <iomanip>
#include <iostream>

namespace CliffordTableaus {
    // Helper functions
    bool QuArray::isPowerOfTwo(std::size_t x) {
        return (x > 0) && ((x & (x - 1)) == 0);
    }


    QuArray::QuArray(std::size_t dim, const std::vector<std::complex<double>> &values, bool measure)
            : N(dim), data(values) {
        if (!isPowerOfTwo(N) || N <= 0 || data.size() != N * N) {
            throw std::invalid_argument("Dimension must be a non-zero power-of-two and values must match dimension.");
        }
        if (!measure && !isUnitary()) {
            throw std::invalid_argument("Non-measure matrix must be unitary upon initialization.");
        }
    }


    QuArray::QuArray(const QuArray &other) = default;

    std::complex<double> QuArray::operator()(std::size_t row, std::size_t col) const {
        return data[row * N + col];
    }

    std::complex<double> &QuArray::operator()(std::size_t row, std::size_t col) {
        return data[row * N + col];
    }

    QuArray QuArray::transpose() const {
        QuArray result(*this);
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < i; ++j) {
                std::swap(result(i, j), result(j, i));
            }
        }
        return result;
    }

    QuArray QuArray::conjugate() const {
        QuArray result(*this);
        for (auto &elem: result.data) {
            elem = std::conj(elem);
        }
        return result;
    }

    QuArray QuArray::dagger() const {
        return this->conjugate().transpose();
    }

    QuArray QuArray::operator+(const QuArray &other) const {
        if (other.N != N) {
            throw std::invalid_argument("Matrix dimension mismatch on addition.");
        }
        QuArray result(*this);
        for (std::size_t i = 0; i < N * N; ++i) {
            result.data[i] += other.data[i];
        }
        return result;
    }

    QuArray QuArray::operator-(const QuArray &other) const {
        if (other.N != N) {
            throw std::invalid_argument("Matrix dimension mismatch on subtraction.");
        }
        QuArray result(*this);
        for (std::size_t i = 0; i < N * N; ++i) {
            result.data[i] -= other.data[i];
        }
        return result;
    }

    QuArray QuArray::operator*(const QuArray &other) const {
        if (other.N != N) {
            throw std::invalid_argument("Matrix dimension mismatch on multiplication.");
        }
        QuArray result(N, std::vector<std::complex<double>>(N * N, std::complex<double>(0, 0)), true);
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                std::complex<double> sum(0, 0);
                for (std::size_t k = 0; k < N; ++k) {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    QuArray QuArray::operator/(const QuArray &other) const {
        if (other.N != N) {
            throw std::invalid_argument("Matrix dimension mismatch on division.");
        }
        // A/B = B^{-1} * A
        return other.inverse() * (*this);
    }

    std::complex<double> QuArray::det() const {
        // Compute determinant via Gaussian elimination (complex)
        // This is a standard algorithm—LU decomposition approach
        // Make a copy
        std::vector<std::complex<double>> temp = data;
        std::complex<double> determinant(1, 0);
        for (std::size_t i = 0; i < N; ++i) {
            // Pivot
            std::size_t pivot = i;
            for (std::size_t r = i + 1; r < N; ++r) {
                if (std::abs(temp[r * N + i]) > std::abs(temp[pivot * N + i])) {
                    pivot = r;
                }
            }
            if (i != pivot) {
                for (std::size_t c = 0; c < N; ++c) {
                    std::swap(temp[i * N + c], temp[pivot * N + c]);
                }
                determinant = -determinant;
            }
            std::complex<double> diag = temp[i * N + i];
            if (std::abs(diag) < 1e-14) {
                return 0.0;
            }
            determinant *= diag;
            for (std::size_t r = i + 1; r < N; ++r) {
                std::complex<double> factor = temp[r * N + i] / diag;
                for (std::size_t c = i; c < N; ++c) {
                    temp[r * N + c] -= factor * temp[i * N + c];
                }
            }
        }
        return determinant;
    }

    QuArray QuArray::inverse() const {
        // Inverse via Gaussian elimination on augmented matrix
        // [A|I] -> [I|A^{-1}]
        QuArray inv(N, std::vector<std::complex<double>>(N * N, std::complex<double>(0, 0)));
        for (std::size_t i = 0; i < N; ++i) {
            inv(i, i) = 1.0;
        }

        std::vector<std::complex<double>> temp = data;
        for (std::size_t i = 0; i < N; ++i) {
            // Pivot
            std::size_t pivot = i;
            for (std::size_t r = i + 1; r < N; ++r) {
                if (std::abs(temp[r * N + i]) > std::abs(temp[pivot * N + i])) {
                    pivot = r;
                }
            }
            if (std::abs(temp[pivot * N + i]) < 1e-14) {
                throw std::runtime_error("Matrix is singular and cannot be inverted.");
            }
            if (i != pivot) {
                for (std::size_t c = 0; c < N; ++c) {
                    std::swap(temp[i * N + c], temp[pivot * N + c]);
                    std::swap(inv(i, c), inv(pivot, c));
                }
            }
            std::complex<double> diag = temp[i * N + i];
            for (std::size_t c = 0; c < N; ++c) {
                temp[i * N + c] /= diag;
                inv(i, c) /= diag;
            }
            for (std::size_t r = 0; r < N; ++r) {
                if (r != i) {
                    std::complex<double> factor = temp[r * N + i];
                    for (std::size_t c = 0; c < N; ++c) {
                        temp[r * N + c] -= factor * temp[i * N + c];
                        inv(r, c) -= factor * inv(i, c);
                    }
                }
            }
        }
        return inv;
    }

    bool QuArray::isUnitary() const {
        // Check if U * U^dagger = I
        QuArray Udag = this->dagger();
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                std::complex<double> sum(0, 0);
                for (std::size_t k = 0; k < N; ++k) {
                    sum += (*this)(i, k) * Udag(k, j);
                }
                if (i == j) {
                    if (std::abs(sum - std::complex<double>(1.0, 0.0)) > 1e-12) {
                        return false;
                    }
                } else {
                    if (std::abs(sum) > 1e-12) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    QuArray &QuArray::operator+=(const QuArray &other) {
        if (other.N != N) {
            throw std::invalid_argument("Dimension mismatch.");
        }
        for (std::size_t i = 0; i < N * N; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    QuArray &QuArray::operator-=(const QuArray &other) {
        if (other.N != N) {
            throw std::invalid_argument("Dimension mismatch.");
        }
        for (std::size_t i = 0; i < N * N; ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    QuArray &QuArray::operator*=(const QuArray &other) {
        if (other.N != N) {
            throw std::invalid_argument("Dimension mismatch.");
        }

        QuArray result(N, std::vector<std::complex<double>>(N * N, std::complex<double>(0, 0)), true);
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                std::complex<double> sum(0, 0);
                for (std::size_t k = 0; k < N; ++k) {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        *this = result;
        return *this;
    }

    QuArray &QuArray::operator/=(const QuArray &other) {
        // A/=B means A = B^{-1} * A
        *this = other.inverse() * (*this);
        return *this;
    }

    QuArray QuArray::operator*(const std::complex<double> &scalar) const {
        QuArray result(*this);
        for (std::size_t i = 0; i < N * N; ++i) {
            result.data[i] *= scalar;
        }
        return result;
    }

    QuArray &QuArray::operator*=(const std::complex<double> &scalar) {
        for (std::size_t i = 0; i < N * N; ++i) {
            data[i] *= scalar;
        }
        return *this;
    }

    QuArray QuArray::operator^(int power) const {
        if (power < 0) {
            QuArray inv = this->inverse();
            QuArray result = inv;
            for (int i = 1; i < -power; ++i) {
                result = result * inv;
            }
            return result;
        } else if (power == 0) {
            // Return identity
            QuArray result(*this);
            for (std::size_t i = 0; i < N * N; ++i) {
                result.data[i] = (i % (N + 1) == 0) ? std::complex<double>(1.0, 0.0) : std::complex<double>(0.0, 0.0);
            }
            return result;
        } else {
            QuArray result(*this);
            QuArray base(*this);
            for (int i = 1; i < power; ++i) {
                result = result * base;
            }
            return result;
        }
    }

    QuArray QuArray::operator&(const QuArray &other) const {
        std::size_t newDim = N * other.N;
        std::vector<std::complex<double>> kronData(newDim * newDim, std::complex<double>(0.0, 0.0));
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                for (std::size_t p = 0; p < other.N; ++p) {
                    for (std::size_t q = 0; q < other.N; ++q) {
                        kronData[(i * other.N + p) * newDim + (j * other.N + q)] = (*this)(i, j) * other(p, q);
                    }
                }
            }
        }
        return {newDim, kronData};
    }

    QuArray &QuArray::operator^=(int power) {
        *this = *this ^ power;
        return *this;
    }

    QuArray &QuArray::operator&=(const QuArray &other) {
        *this = *this & other;
        return *this;
    }


    uint32_t QuArray::dim2n(uint32_t dim) {
        // Determine the number of qubits
        // dim = 2^n -> n = log2(dim)
        std::size_t n = 0;
        {
            std::size_t tmp = dim;
            while (tmp > 1) {
                tmp >>= 1;
                n++;
            }
        }
        if ((1ULL << n) != dim) {
            throw std::invalid_argument("Dimension must be a power of two.");
        }
        return n;
    }

    QuArray QuArray::MeasureZero() {
        return QuArray(2, {1.0, 0.0, 0.0, 0.0}, true);
    }

    QuArray QuArray::MeasureOne() {
        return QuArray(2, {0.0, 0.0, 0.0, 1.0}, true);
    }

    QuArray QuArray::Identity() {
        return QuArray(2, {1.0, 0.0, 0.0, 1.0});
    }

    QuArray QuArray::PauliX() {
        return QuArray(2, {0.0, 1.0, 1.0, 0.0});
    }

    QuArray QuArray::PauliY() {
        return QuArray(2, {0.0, -1.0i, 1.0i, 0.0});
    }

    QuArray QuArray::PauliZ() {
        return QuArray(2, {1.0, 0.0, 0.0, -1.0});
    }

    QuArray QuArray::Hadamard() {
        return QuArray(2, {h_factor, h_factor, h_factor, -h_factor});
    }

    QuArray QuArray::Phase() {
        return QuArray(2, {1.0, 0.0, 0.0, 1.0i});
    }

    QuArray QuArray::TGate() {
        return QuArray(2, {1.0, 0.0, 0.0, std::complex<double>(h_factor, h_factor)});
    }

    QuArray QuArray::RotationX(double theta) {
        auto cos_t = std::cos(0.5 * theta);
        auto sin_t = std::sin(0.5 * theta);
        return QuArray(2, {
                cos_t, -1.0i * sin_t,
                -1.0i * sin_t, cos_t
        });
    }

    QuArray QuArray::RotationY(double theta) {
        auto cos_t = std::cos(0.5 * theta);
        auto sin_t = std::sin(0.5 * theta);
        return QuArray(2, {
                cos_t, -sin_t,
                sin_t, cos_t
        });
    }

    QuArray QuArray::RotationZ(double theta) {
        return QuArray(2, {
                std::exp(-0.5i * theta), 0.0,
                0.0, std::exp(0.5i * theta)
        });
    }


    QuArray QuArray::ControlGate(std::size_t dim, std::size_t control, std::size_t target, const QuArray &gate) {
        auto n = dim2n(dim);
        if (control >= n || target >= n || control == target) {
            throw std::invalid_argument("Invalid control/target indices.");
        }
        if (gate.size() != 2) {
            throw std::invalid_argument("Gate to apply must be 2x2.");
        }

        // Define simple 2x2 matrices
        QuArray I = QuArray::Identity();
        QuArray M0 = MeasureZero();
        QuArray M1 = MeasureOne();

        // Build the first part: M0 at control and I elsewhere
        QuArray first_factor = QuArray(1, {1.0}, true);
        for (std::size_t qubit = 0; qubit < n; ++qubit) {
            if (qubit == control) {
                first_factor &= M0;
            } else {
                first_factor &= I;
            }
        }

        // Build the second part: M1 at control, X at target, I elsewhere
        QuArray second_factor = QuArray(1, {1.0}, true);
        for (std::size_t qubit = 0; qubit < n; ++qubit) {
            if (qubit == control) {
                second_factor &= M1;
            } else if (qubit == target) {
                second_factor &= gate;
            } else {
                second_factor &= I;
            }
        }

        // The full Control gate is first_factor + second_factor
        return first_factor + second_factor;
    }

    QuArray QuArray::DoubleControlGate(
            std::size_t dim, std::size_t control1, std::size_t control2, std::size_t target, const QuArray &gate
    ) {
        auto n = dim2n(dim);
        if (control1 >= n || control2 >= n || target >= n ||
            control1 == control2 || control1 == target || control2 == target) {
            throw std::invalid_argument("Invalid qubit indices for double control gate.");
        }
        if (gate.size() != 2) {
            throw std::invalid_argument("Gate must be 2x2.");
        }

        QuArray I = QuArray::Identity();
        QuArray M0 = QuArray::MeasureZero();
        QuArray M1 = QuArray::MeasureOne();

        // "00" submatrix: M0 at control1, M0 at control2, I elsewhere
        QuArray result00(1, {1.0}, true);
        for (std::size_t qubit = 0; qubit < n; ++qubit) {
            if (qubit == control1 || qubit == control2) {
                result00 &= M0;
            } else {
                result00 &= I;
            }
        }

        // "01" submatrix: M0 at control1, M1 at control2, I elsewhere
        QuArray result01(1, {1.0}, true);
        for (std::size_t qubit = 0; qubit < n; ++qubit) {
            if (qubit == control1) {
                result01 &= M0;
            } else if (qubit == control2) {
                result01 &= M1;
            } else {
                result01 &= I;
            }
        }

        // "10" submatrix: M1 at control1, M0 at control2, I elsewhere
        QuArray result10(1, {1.0}, true);
        for (std::size_t qubit = 0; qubit < n; ++qubit) {
            if (qubit == control1) {
                result10 &= M1;
            } else if (qubit == control2) {
                result10 &= M0;
            } else {
                result10 &= I;
            }
        }

        // "11" submatrix: M1 at control1, M1 at control2, gate at target, I elsewhere
        QuArray result11(1, {1.0}, true);
        for (std::size_t qubit = 0; qubit < n; ++qubit) {
            if (qubit == control1 || qubit == control2) {
                result11 &= M1;
            } else if (qubit == target) {
                result11 &= gate;
            } else {
                result11 &= I;
            }
        }

        // Sum up all submatrices
        return result00 + result01 + result10 + result11;
    }


    QuArray QuArray::CNOT(std::size_t dim, std::size_t control, std::size_t target) {
        return ControlGate(dim, control, target, PauliX());
    }

    QuArray QuArray::Toffoli(std::size_t dim, std::size_t control1, std::size_t control2, std::size_t target) {
        return DoubleControlGate(dim, control1, control2, target, PauliX());
    }

    QuArray QuArray::SWAP(std::size_t dim, std::size_t qubit1, std::size_t qubit2) {
        auto n = dim2n(dim);
        if (qubit1 >= n || qubit2 >= n || qubit1 == qubit2) {
            throw std::invalid_argument("Invalid qubit indices for SWAP.");
        }

        std::vector<std::complex<double>> mat(dim * dim, std::complex<double>(0.0, 0.0));

        // Helper lambda to swap bits in index
        auto swap_bits = [qubit1, qubit2](std::size_t x) {
            std::size_t bit1 = (x >> qubit1) & 1ULL;
            std::size_t bit2 = (x >> qubit2) & 1ULL;

            // If bits differ, swap them
            if (bit1 != bit2) {
                x ^= (1ULL << qubit1);
                x ^= (1ULL << qubit2);
            }
            return x;
        };

        // Build the permutation matrix
        for (std::size_t i = 0; i < dim; ++i) {
            std::size_t j = swap_bits(i);
            mat[j * dim + i] = 1.0;
        }

        // This is a unitary, so no measure flag
        return {dim, mat};
    }


    QuArray QuArray::Fredkin(std::size_t dim, std::size_t control, std::size_t target1, std::size_t target2) {
        auto n = dim2n(dim);
        if (control >= n || target1 >= n || target2 >= n || target1 == target2) {
            throw std::invalid_argument("Invalid qubit indices for Fredkin.");
        }

        QuArray I = QuArray::Identity();
        QuArray M0 = QuArray::MeasureZero();
        QuArray M1 = QuArray::MeasureOne();

        // Part when control=0: M0 at control, I at other qubits
        QuArray part0(1, {1.0}, true);
        for (std::size_t q = 0; q < n; ++q) {
            if (q == control) {
                part0 &= M0;
            } else {
                part0 &= I;
            }
        }

        // Part when control=1: M1 at control, I at others (initially no operation on targets)
        QuArray part1(1, {1.0}, true);
        for (std::size_t q = 0; q < n; ++q) {
            if (q == control) {
                part1 &= M1;
            } else {
                part1 &= I;
            }
        }

        // Now apply SWAP operation on target1 and target2 only if control=1
        // The SWAP function returns the full NxN operator performing swap on target1,target2
        QuArray swap_op = QuArray::SWAP(dim, target1, target2);

        // Combine the parts:
        // If control=0: no swap, just part0
        // If control=1: swap, so part1 * swap_op
        return part0 + (part1 * swap_op);
    }

    QuArray QuArray::RandomUnitary() {
        const double lower_bound = 0.0;
        const double upper_bound = 2.0 * M_PI;

        std::random_device randomDevice;
        std::mt19937 gen(randomDevice());
        std::uniform_real_distribution<> distribution(lower_bound, upper_bound);

        double alpha = distribution(gen);
        double beta = distribution(gen);
        double gamma = distribution(gen);
        double delta = distribution(gen);

        // Theorem 4.1: Z-Y decomposition for a single qubit
        // Suppose U is a unitary operation on a single qubit.
        // Then there exist real numbers α, β, γ and δ such that
        // U = e^(iα) * Rz(β) * Ry(γ) * Rz(δ)
        // The array of gates <rz-ry-rz> is chosen because it has the potential
        // to perform any feasible unitary operation without global phase shift.
        return QuArray::RotationZ(beta) * QuArray::RotationY(gamma) * QuArray::RotationZ(delta) * exp(1i * alpha);
    }

    void QuArray::print() const {
        const char *top_left = "⎡";
        const char *top_right = "⎤";
        const char *mid_left = "⎢";
        const char *mid_right = "⎥";
        const char *bot_left = "⎣";
        const char *bot_right = "⎦";

        auto format_number = [](double val) {
            // Check if it's close to an integer
            double rounded = std::round(val);
            if (std::abs(val - rounded) < 1e-14) {
                // Print as integer
                std::ostringstream oss;
                oss << static_cast<long long>(static_cast<long long>(rounded));
                return oss.str();
            } else {
                // Print as shorter decimal, strip trailing zeros
                std::ostringstream oss;
                oss << std::defaultfloat << std::setprecision(6) << val;
                std::string str = oss.str();

                // Strip trailing zeros and a trailing decimal point if needed
                if (str.find('.') != std::string::npos) {
                    while (!str.empty() && (str.back() == '0')) {
                        str.pop_back();
                    }
                    if (!str.empty() && str.back() == '.') {
                        str.pop_back();
                    }
                }

                return str;
            }
        };

        auto print_complex = [&](std::complex<double> val) {
            double re = val.real();
            double im = val.imag();

            // Handle near-zero as zero
            if (std::abs(re) < 1e-14) re = 0.0;
            if (std::abs(im) < 1e-14) im = 0.0;

            if (re == 0.0 && im == 0.0) {
                return std::string("0");
            } else if (im == 0.0) {
                return format_number(re);
            } else if (re == 0.0) {
                // Pure imaginary
                if (std::abs(im - 1.0) < 1e-14) {
                    return std::string("1⋅ⅈ");
                } else if (std::abs(im + 1.0) < 1e-14) {
                    return std::string("-1⋅ⅈ");
                } else {
                    return format_number(im) + "⋅ⅈ";
                }
            } else {
                // Complex number with both parts
                std::string real_part = format_number(re);
                std::string imag_part = format_number(std::abs(im));
                if (im > 0) {
                    return real_part + " + " + imag_part + "⋅ⅈ";
                } else {
                    return real_part + " - " + imag_part + "⋅ⅈ";
                }
            }
        };

        for (std::size_t i = 0; i < N; ++i) {
            if (i == 0) {
                std::cout << "\t" << top_left;
            } else if (i == N - 1) {
                std::cout << "\t" << bot_left;
            } else {
                std::cout << "\t" << mid_left;
            }

            for (std::size_t j = 0; j < N; ++j) {
                std::cout << print_complex((*this)(i, j));
                if (j < N - 1) std::cout << "       ";
            }

            if (i == 0) {
                std::cout << top_right << "\n";
            } else if (i == N - 1) {
                std::cout << bot_right << "\n";
            } else {
                std::cout << mid_right << "\n";
            }
        }
        std::cout << std::endl;
    }

}
