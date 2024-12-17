#pragma once

#include <cstdint>
#include <array>
#include <complex>
#include <vector>
#include <stdexcept>


namespace CliffordTableaus {
    using namespace std::complex_literals;
    using uint = std::size_t;

    class QuArray {
    private:
        std::size_t N;
        std::vector<std::complex<double>> data;

        [[nodiscard]] bool isUnitary() const;

        static inline double h_factor = 0.707106781186547;
    public:
        // Constructor taking a dimension and an initializer list of values (row-major)
        // Override unitarity check for measure matrices
        QuArray(std::size_t dim, const std::vector<std::complex<double>> &values, bool measure = false);

        // Copy constructor
        QuArray(const QuArray &other);

        // Basic operations
        [[nodiscard]] QuArray transpose() const;

        [[nodiscard]] QuArray conjugate() const;

        /**
         * The conjugate transpose of a matrix.
         * @return The conjugate transpose of the matrix.
         */
        [[nodiscard]] QuArray dagger() const;

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
        [[nodiscard]] std::complex<double> det() const;

        [[nodiscard]] QuArray inverse() const;

        // Dimension accessor
        [[nodiscard]] std::size_t size() const { return N; }

        // Element accessor
        std::complex<double> operator()(std::size_t row, std::size_t col) const;

        std::complex<double> &operator()(std::size_t row, std::size_t col);

        static bool isPowerOfTwo(std::size_t x);

        static uint32_t dim2n(uint32_t dim);

        static QuArray MeasureZero();

        static QuArray MeasureOne();

        static QuArray Identity();

        static QuArray PauliX();

        static QuArray PauliY();

        static QuArray PauliZ();

        /**
         * The Hadamard factor is:
         * 1/sqrt(2) = 0.707106781186547.
         * Use it to construct the Hadamard gate.
         * @return The Hadamard gate for 1 qubit.
         */
        static QuArray Hadamard();

        static QuArray Phase();

        static QuArray TGate();

        static QuArray RotationX(double theta);

        static QuArray RotationY(double theta);

        static QuArray RotationZ(double theta);

        static QuArray ControlGate(std::size_t dim, std::size_t control, std::size_t target, const QuArray &gate);

        static QuArray DoubleControlGate(
                std::size_t dim, std::size_t control1, std::size_t control2, std::size_t target, const QuArray &gate
        );

        static QuArray CNOT(std::size_t dim, std::size_t control, std::size_t target);

        static QuArray Toffoli(std::size_t dim, std::size_t control1, std::size_t control2, std::size_t target);

        static QuArray SWAP(std::size_t dim, std::size_t qubit1, std::size_t qubit2);

        static QuArray Fredkin(std::size_t dim, std::size_t control, std::size_t target1, std::size_t target2);

        static QuArray RandomUnitary();

        void print() const;
    };
}

