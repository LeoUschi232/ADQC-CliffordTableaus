#pragma once

#include <stdexcept>
#include <cstdint>
#include <vector>

namespace CliffordTableaus {
    using uint = std::size_t;

    class Tableau {
    private:
        uint n;
        uint total_bits;
        std::vector<uint8_t> generators;

        void set(uint index, uint8_t value);

        uint8_t get(uint index);

    public:
        Tableau(uint n) : n(n), total_bits(2 * n * (2 * n + 1)), generators((total_bits + 7) / 8, 0) {}

        void set_x(uint i, uint j, uint8_t x);

        void set_z(uint i, uint j, uint8_t z);

        void set_r(uint i, uint8_t r);

        uint8_t get_x(uint i, uint j);

        uint8_t get_z(uint i, uint j);

        uint8_t get_r(uint i);

        uint8_t get_xz(uint ix, uint jx, uint iz, uint jz);

        static char interpret(uint8_t xz);
    };


}
