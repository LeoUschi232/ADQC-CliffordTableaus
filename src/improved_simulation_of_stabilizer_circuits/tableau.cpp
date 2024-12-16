#include "tableau.h"


#include <cstdint>
#include <vector>

namespace CliffordTableaus {

    void Tableau::set(uint index, uint8_t value) {
        uint byte_index = index / 8;
        uint bit_index = index % 8;
        generators[byte_index] &= ~(1 << bit_index);
        generators[byte_index] |= value << bit_index;
    }

    void Tableau::set_x(uint i, uint j, uint8_t x) {
        if (i >= 2 * n || j >= n) {
            throw std::invalid_argument("Invalid indices for set_x.");
        }
        // Shift the index starting at 1 to index starting at 0
        set((i - 1) * (2 * n + 1) + (j - 1), x);
    }

    void Tableau::set_z(uint i, uint j, uint8_t z) {
        if (i >= 2 * n || j >= n) {
            throw std::invalid_argument("Invalid indices for set_z.");
        }
        // Shift the index starting at 1 to index starting at 0
        set((i - 1) * (2 * n + 1) + n + (j - 1), z);
    }

    void Tableau::set_r(uint i, uint8_t r) {
        if (i >= 2 * n) {
            throw std::invalid_argument("Invalid index for set_r.");
        }
        // Shift the index starting at 1 to index starting at 0
        set((i - 1) * (2 * n + 1) + 2 * n, r);
    }

    uint8_t Tableau::get(uint index) {
        uint byte_index = index / 8;
        uint bit_index = index % 8;
        return (generators[byte_index] >> bit_index) & 1;
    }

    uint8_t Tableau::get_x(uint i, uint j) {
        if (i >= 2 * n || j >= n) {
            throw std::invalid_argument("Invalid indices for get_x.");
        }
        // Shift the index starting at 1 to index starting at 0
        return get((i - 1) * (2 * n + 1) + (j - 1));
    }

    uint8_t Tableau::get_z(uint i, uint j) {
        if (i >= 2 * n || j >= n) {
            throw std::invalid_argument("Invalid indices for get_z.");
        }
        // Shift the index starting at 1 to index starting at 0
        return get((i - 1) * (2 * n + 1) + n + (j - 1));
    }

    uint8_t Tableau::get_r(uint i) {
        if (i >= 2 * n) {
            throw std::invalid_argument("Invalid index for get_r.");
        }
        // Shift the index starting at 1 to index starting at 0
        return get((i - 1) * (2 * n + 1) + 2 * n);
    }

    uint8_t Tableau::get_xz(uint ix, uint jx, uint iz, uint jz) {
        return (get_x(ix, jx) << 1) & get_z(iz, jz);
    }

    char Tableau::interpret(uint8_t xz) {
        switch (xz & 0b11) {
            case 0b00:
                return 'I';
            case 0b01:
                return 'Z';
            case 0b10:
                return 'X';
            case 0b11:
                return 'Y';
            default:
                throw std::invalid_argument("Invalid input.");
        }
    }
}
