#pragma once

#include "subroutines.h"
#include "stabilizer_tableau.h"

#include <cstdint>
#include <stdexcept>
#include <cstdint>
#include <vector>

namespace CliffordTableaus {
    using uint = std::size_t;

    /**
     * Improved stabilizer tableaus for a new simulation algorithm, by which both deterministic
     * and random measurements can be performed in O (n^2) time.
     * The cost is a factor-2 increase in the number of bits needed to specify a state.
     * For in addition to the n stabilizer generators, we now store n “destabilizer” generators,
     * which are Pauli operators that together with the stabilizer generators generate the full Pauli group Pn.
     * So the number of bits needed is 2*n*(2*n+1)=4*n^2+2*n.
     */
    class ImprovedStabilizerTableau : public StabilizerTableau {
    private:
        /**
         * The algorithm uses a subroutine called rowsum (h, i), which sets generator h equal to i + h.
         * Its purpose is to keep track, in particular, of the phase bit rh, including all the factors of i
         * that appear when multiplying Pauli matrices.
         * @param h The generator to update.
         * @param i The generator to add to h.
         */
        void rowsum(int h, int i);

        /**
         * Set the value of a bit in the tableau.
         * @param index The position of the bit.
         * @param value The value to which to set the bit to.
         */
        void set(uint index, uint8_t value);

        /**
         * Get the value of a bit in the tableau.
         * @param index The position of the bit.
         * @return The value of the bit.
         */
        uint8_t get(uint index);

    public:
        /**
         * Construct a new ImprovedStabilizerTableau object.
         */
        ImprovedStabilizerTableau() = default;

        /**
         * Initialize the tableau with the given number of qubits and total bits.
         * The entries of the tableau will be default initialized to the state |0〉^(⊗n).
         * This state is represented by a tableau with its (2n)x(2n) submatrix set to identity.
         * @param p_n Number of qubits in the system.
         * @param p_total_bits Number of bits necessary to specify the state using the tableau.
         */
        void initializeTableau(uint p_n) override;

        /// Superclass overrides begin.
        void CNOT(uint control, uint target) override;

        void Hadamard(uint qubit) override;

        void Phase(uint qubit) override;

        uint8_t Measurement(uint qubit) override;
        /// Superclass overrides end.

        /**
         * Set the value of the x operator bit for a qubit.
         * @param i Index of the generator.
         * @param j Index of qubit.
         * @param x Value of the x operator bit.
         */
        void set_x(uint i, uint j, uint8_t x);

        /**
         * Set the value of the z operator bit for a qubit.
         * @param i Index of the generator.
         * @param j Index of qubit.
         * @param z Value of the z operator bit.
         */
        void set_z(uint i, uint j, uint8_t z);

        /**
         * Set the value of the phase operator bit for a qubit.
         * @param i Index of the generator.
         * @param r Value of the phase operator bit.
         */
        void set_r(uint i, uint8_t r);

        /**
         * Set the value of the xz-combination for a qubit.
         * @param i Index of the generator.
         * @param j Index of qubit.
         * @param xz Value of the xz-combination.
         */
        void set_xz(uint i, uint j, uint8_t xz);

        /**
         * Get the value of the x operator bit for a qubit.
         * @param i Index of the generator.
         * @param j Index of qubit.
         */
        uint8_t get_x(uint i, uint j);

        /**
         * Get the value of the z operator bit for a qubit.
         * @param i Index of the generator.
         * @param j Index of qubit.
         */
        uint8_t get_z(uint i, uint j);

        /**
         * Get the value of the phase operator bit for a qubit.
         * @param i Index of the generator.
         */
        uint8_t get_r(uint i);

        /**
         * Get the value of the xz-combination for a qubit.
         * @param i Index of the generator.
         * @param j Index of qubit.
         * @return The value of the xz-combination.
         */
        uint8_t get_xz(uint i, uint j);

        /**
         * Interpret the xz-combination as a Pauli operator.
         * @param xz Combination of x and z bits.
         * @return 00 => 'I', 01 => 'Z', 10 => 'X', 11 => 'Y'.
         */
        static char interpret(uint8_t xz);

        /**
         * Reverse interpretation of a Pauli operator.
         * @param pauli Either 'I', 'Z', 'X', or 'Y'. Everything else will throw an error.
         * @return The corresponding xz-combination.
         */
        static uint8_t reverse_interpret(char pauli);

    };
}