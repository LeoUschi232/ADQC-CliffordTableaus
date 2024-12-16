#pragma once

#include <cstdint>

namespace CliffordTableaus {
    /**
     * Let g (x1, z1, x2, z2) be a function that takes 4 bits as input, and that returns the exponent
     * to which i is raised (either 0, 1, or −1) when the Pauli matrices represented by x1z1 and x2z2 are multiplied.
     * More explicitly:
     * if x1=z1=0 then g=0;
     * if x1=z1 = 1 then g=z2−x2;
     * if x1=1 and z1=0 then g=z2*(2*x2−1);
     * if x1=0 and z1=1 then g=x2*(1−2*z2).
     * @param x1z1x2z2 The 4 input bits stored in the least significant bits of an 8-bit unsigned integer.
     * @return The exponent to which i is raised when the Pauli matrices represented by x1z1 and x2z2 are multiplied.
     */
    int g(uint8_t x1z1x2z2);

    /**
     * The algorithm uses a subroutine called rowsum (h, i), which sets generator h equal to i + h.
     * Its purpose is to keep track, in particular, of the phase bit rh, including all the factors of i
     * that appear when multiplying Pauli matrices.
     * @param h The generator to update.
     * @param i The generator to add to h.
     * @return The updated generator h.
     */
    int rowsum(int h, int i);

}