#pragma once

#include <cstdint>
#include <array>
#include <complex>
#include <vector>
#include <stdexcept>


namespace CliffordTableaus {
    class QuArray {
    private:
        std::size_t N;
        std::vector<std::complex<double>> data;

        bool isUnitary() const;

    public:
        // Constructor taking a dimension and an initializer list of values (row-major)
        QuArray(std::size_t dim, const std::vector<std::complex<double>> &values);

        // Copy constructor
        QuArray(const QuArray &other);

        // Basic operations
        QuArray transpose() const;

        QuArray conjugate() const;

        /**
         * The conjugate transpose of a matrix.
         * @return The conjugate transpose of the matrix.
         */
        QuArray dagger() const;

        // Arithmetic operations
        QuArray operator*(const std::complex<double> &scalar) const;

        QuArray operator+(const QuArray &other) const;

        QuArray operator-(const QuArray &other) const;

        QuArray operator*(const QuArray &other) const;

        /**
         * Matrix by matrix division is here defined as A/B = B^(-1)*A
         * @param other The matrix to divide by.
         * @return The value (other^(-1))*this.
         */
        QuArray operator/(const QuArray &other) const;

        QuArray &operator*=(const std::complex<double> &scalar);

        QuArray &operator+=(const QuArray &other);

        QuArray &operator-=(const QuArray &other);

        QuArray &operator*=(const QuArray &other);

        QuArray &operator/=(const QuArray &other);

        // Advanced operations
        /**
         * Matrix exponentiation.
         * @param power The power to raise the matrix to.
         * @return The matrix raised to the power.
         */
        QuArray operator^(int power) const;

        /**
         * Matrix Tensor product.
         * @param other The matrix to tensor with.
         * @return The Tensor product of the two matrices.
         */
        QuArray operator&(const QuArray &other) const;

        QuArray &operator^=(int power);

        QuArray &operator&=(const QuArray &other);


        // Determinant and inverse
        std::complex<double> det() const;

        QuArray inverse() const;

        // Dimension accessor
        std::size_t size() const { return N; }

        // Element accessor
        std::complex<double> operator()(std::size_t row, std::size_t col) const;

        std::complex<double> &operator()(std::size_t row, std::size_t col);

        static bool isPowerOfTwo(std::size_t x);
    };
}

