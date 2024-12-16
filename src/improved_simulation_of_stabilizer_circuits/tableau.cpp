#include "tableau.h"


#include <cstdint>
#include <vector>

namespace CliffordTableaus {
    Tableau::Tableau(uint n) : n(n), total_bits(2 * n * (2 * n + 1)), generators((total_bits + 7) / 8, 0) {
        for (int i = 0; i < 2 * n; ++i) {
            set(i * (2 * n + 1) + i, 1);
        }
    }

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

    void Tableau::set_xz(uint i, uint j, uint8_t xz) {
        set_x(i, j, (xz >> 1) & 1);
        set_z(i, j, xz & 1);
    }

    void Tableau::set_xz(uint i, uint j, char pauli) {
        set_xz(i, j, reverse_interpret(pauli));
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

    uint8_t Tableau::get_xz(uint i, uint j) {
        return (get_x(i, j) << 1) & get_z(i, j);
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

    uint8_t reverse_interpret(char pauli) {
        switch (pauli) {
            case 'I':
                return 0b00;
            case 'Z':
                return 0b01;
            case 'X':
                return 0b10;
            case 'Y':
                return 0b11;
            default:
                throw std::invalid_argument("Invalid input.");
        }
    }
}
