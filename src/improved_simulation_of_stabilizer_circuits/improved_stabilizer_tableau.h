#pragma once

#include "subroutines.h"
#include "stabilizer_tableau.h"

#include <iostream>
#include <cassert>
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
         * It will be convenient to add an additional (2n + 1)st row for scratch space.
         * Using this scratch space allows one to override valid qubit index checks.
         * Use only when performing a measurement.
         */
        bool using_scratch_space = false;

        /**
         * The algorithm uses a subroutine called rowsum (h, i), which sets generator h equal to i + h.
         * Its purpose is to keep track, in particular, of the phase bit rh, including all the factors of i
         * that appear when multiplying Pauli matrices.
         * The function rowsum represents the group operation in Pn.
         * This means whichever matrix is represented by h is multiplied by the matrix represented by i
         * The result are the bits of the matrix represented by hi stored in row h.
         * @param h The generator to update.
         * @param i The generator to add to h.
         */
        void rowsum(uint h, uint i);

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

        /**
         * Throws an invalid argument exception with the given message if the scratch space is not being used.
         * @param message Message to pass to std::invalid_argument.
         */
        void throw_invalid_argument(const std::string &message) const;

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
         * Get the value of the phase operator bit-pair for a qubit.
         * The r variable consists of 2 bits to encode the possible values: 1, i, -1, -i.
         * @param i Index of the generator.
         */
        uint8_t get_r(uint i);
    };
}
