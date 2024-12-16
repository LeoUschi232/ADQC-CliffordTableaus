#include "quarray.h"
#include <cmath>
#include <algorithm>

namespace CliffordTableaus {
    // Helper functions
    bool QuArray::isPowerOfTwo(std::size_t x) {
        return (x > 0) && ((x & (x - 1)) == 0);
    }

    QuArray::QuArray(std::size_t dim, const std::vector<std::complex<double>> &values)
            : N(dim), data(values) {
        if (!isPowerOfTwo(N) || N <= 0 || data.size() != N * N) {
            throw std::invalid_argument("Dimension must be a non-zero power-of-two and values must match dimension.");
        }
        if (!isUnitary()) {
            throw std::invalid_argument("Matrix must be unitary upon initialization.");
        }
    }

    QuArray::QuArray(const QuArray &other)
            : N(other.N), data(other.data) {}

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
        QuArray result(N, std::vector<std::complex<double>>(N * N, std::complex<double>(0, 0)));
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

        QuArray result(N, std::vector<std::complex<double>>(N * N, std::complex<double>(0, 0)));
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
        return QuArray(newDim, kronData);
    }
}
