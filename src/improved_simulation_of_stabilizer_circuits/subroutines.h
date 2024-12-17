#pragma once

#include <cstdint>
#include <random>
#include <stdexcept>

namespace CliffordTableaus {
    /**
     * Random device for generating random bits.
     */
    static std::random_device randomDevice;

    /**
     * Mersenne Twister engine for generating random bits.
     */
    static std::mt19937 generator(randomDevice());

    /**
     * Uniform distribution for generating random bits.
     */
    static std::uniform_int_distribution<> distribution(0, 1);

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
     * Generate a random bit, either 0 or 1 with equal probability.
     * @return Random bit, either 0 or 1.
     */
    uint8_t random_bit();
}