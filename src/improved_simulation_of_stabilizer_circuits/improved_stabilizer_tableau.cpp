#include "improved_stabilizer_tableau.h"

namespace CliffordTableaus {
    void ImprovedStabilizerTableau::initializeTableau(uint p_n) {
        StabilizerTableau::initializeTableau(p_n, (2 * n + 1) * (2 * n + 1));
        for (int i = 0; i <= 2 * n; ++i) {
            set(i * (2 * n + 1) + i, 1);
        }

    }

    void ImprovedStabilizerTableau::CNOT(uint control, uint target) {
        if (control >= n || target >= n || control == target) {
            throw std::invalid_argument("Invalid control or target qubit.");
        }

        auto a = control;
        auto b = target;
        for (int i = 1; i <= 2 * n; ++i) {
            auto xia_zib = get_x(i, a) & get_z(i, b);
            auto xib_zia_1 = get_x(i, b) ^ get_z(i, a) ^ 1;
            set_r(i, get_r(i) ^ (xia_zib & xib_zia_1));
            set_x(i, b, get_x(i, b) ^ get_x(i, a));
            set_z(i, a, get_z(i, a) ^ get_z(i, b));
        }
    }

    void ImprovedStabilizerTableau::Hadamard(uint qubit) {
        if (qubit >= n) {
            throw std::invalid_argument("Invalid qubit index.");
        }

        auto a = qubit;
        for (int i = 1; i <= 2 * n; ++i) {
            set_r(i, get_r(i) ^ (get_x(i, a) & get_z(i, a)));
            auto new_xia = get_z(i, a);
            auto new_zia = get_x(i, a);
            set_x(i, a, new_xia);
            set_z(i, a, new_zia);
        }
    }

    void ImprovedStabilizerTableau::Phase(uint qubit) {
        if (qubit >= n) {
            throw std::invalid_argument("Invalid qubit index.");
        }

        auto a = qubit;
        for (int i = 1; i <= 2 * n; ++i) {
            set_r(i, get_r(i) ^ (get_x(i, a) & get_z(i, a)));
            set_z(i, a, get_z(i, a) ^ get_x(i, a));
        }
    }

    uint8_t ImprovedStabilizerTableau::Measurement(uint qubit) {
        if (qubit >= n) {
            throw std::invalid_argument("Invalid qubit index.");
        }

        // Measurement of qubit a in standard basis.
        // First check whether there exists a p with n+1<=p<=2*n such that xpa=1.
        auto a = qubit;
        uint p;
        for (p = n + 1; p <= 2 * n; ++p) {
            if (get_x(p, a) == 1) {
                break;
            }
        }
        if (p <= 2 * n) {
            // Case I: Such a p exists.
            // If more than one exists, then let p be the smallest.
            // In this case the measurement outcome is random, so the state needs to be updated.
            // This is done as follows.
            // First call rowsum(i,p) for all i ∈ {1 to 2*n} such that i=/=p and xia = 1.
            for (int i = 1; i <= 2 * n; ++i) {
                if (i != p && get_x(i, a) == 1) {
                    rowsum(i, (int) p);
                }
            }

            // Second, set the entire (p−n)th row equal to the pth row.
            for (int j = 1; j <= n; ++j) {
                set_xz(p - n, j, get_xz(p, j));
            }
            set_r(p - n, get_r(p));

            // Third, set the pth row to be identically 0,
            // except that rp is 0 or 1 with equal probability,
            // and zpa = 1.
            for (int i = 1; i <= 2 * n; ++i) {
                set_xz(p, i, 0);
            }
            set_r(p, random_bit());
            set_z(p, a, 1);

            // Finally, return rp as the measurement outcome.
            return get_r(p);
        }

        // Case II: Such a p does not exist.
        // In this case the outcome is determinate, so measuring the state will not change it.
        // The only task is to determine whether 0 or 1 is observed.
        // This is done as follows.
        // First set the (2n+1)st row to be identically 0.
        for (int j = 1; j <= n; ++j) {
            set_xz(2 * n + 1, j, 0);
        }
        set_r(2 * n + 1, 0);

        // Second, call rowsum (2n+1,i+n) for all i ∈ {1 to n} such that xia = 1.
        for (int i = 1; i <= n; ++i) {
            if (get_x(i, a) == 1) {
                rowsum(2 * (int) n + 1, i + (int) n);
            }
        }

        // Finally return r_{2n+1} as the measurement outcome.
        return get_r(2 * n + 1);
    }

    void ImprovedStabilizerTableau::rowsum(int h, int i) {
        auto rh = get_r(h);
        auto ri = get_r(i);

        int sum_g = 2 * (rh + ri);
        for (int j = 1; j <= n; ++j) {
            sum_g += g((get_xz(i, j) << 2) | get_xz(h, j));
        }
        if (sum_g % 4 == 0) {
            set_r(h, 0);
        } else if (sum_g % 4 == 2) {
            set_r(h, 1);
        } else {
            throw std::logic_error("The sum of rh, ri and g should never be congruent to 1 or 3.");
        }

        for (int j = 1; j <= n; ++j) {
            set_x(h, j, get_x(i, j) ^ get_x(h, j));
            set_z(h, j, get_z(i, j) ^ get_z(h, j));
        }
    }


    void ImprovedStabilizerTableau::set(uint index, uint8_t value) {
        uint byte_index = index / 8;
        uint bit_index = index % 8;
        tableau[byte_index] &= ~(1 << bit_index);
        tableau[byte_index] |= value << bit_index;
    }

    uint8_t ImprovedStabilizerTableau::get(uint index) {
        uint byte_index = index / 8;
        uint bit_index = index % 8;
        return (tableau[byte_index] >> bit_index) & 1;
    }

    void ImprovedStabilizerTableau::set_x(uint i, uint j, uint8_t x) {
        if (i >= 2 * n || j >= n) {
            throw std::invalid_argument("Invalid indices for set_x.");
        }
        // Shift the index starting at 1 to index starting at 0
        set((i - 1) * (2 * n + 1) + (j - 1), x);
    }

    void ImprovedStabilizerTableau::set_z(uint i, uint j, uint8_t z) {
        if (i >= 2 * n || j >= n) {
            throw std::invalid_argument("Invalid indices for set_z.");
        }
        // Shift the index starting at 1 to index starting at 0
        set((i - 1) * (2 * n + 1) + n + (j - 1), z);
    }

    void ImprovedStabilizerTableau::set_r(uint i, uint8_t r) {
        if (i >= 2 * n) {
            throw std::invalid_argument("Invalid index for set_r.");
        }
        // Shift the index starting at 1 to index starting at 0
        set((i - 1) * (2 * n + 1) + 2 * n, r);
    }

    void ImprovedStabilizerTableau::set_xz(uint i, uint j, uint8_t xz) {
        set_x(i, j, (xz >> 1) & 1);
        set_z(i, j, xz & 1);
    }


    uint8_t ImprovedStabilizerTableau::get_x(uint i, uint j) {
        if (i >= 2 * n || j >= n) {
            throw std::invalid_argument("Invalid indices for get_x.");
        }
        // Shift the index starting at 1 to index starting at 0
        return get((i - 1) * (2 * n + 1) + (j - 1));
    }

    uint8_t ImprovedStabilizerTableau::get_z(uint i, uint j) {
        if (i >= 2 * n || j >= n) {
            throw std::invalid_argument("Invalid indices for get_z.");
        }
        // Shift the index starting at 1 to index starting at 0
        return get((i - 1) * (2 * n + 1) + n + (j - 1));
    }

    uint8_t ImprovedStabilizerTableau::get_r(uint i) {
        if (i >= 2 * n) {
            throw std::invalid_argument("Invalid index for get_r.");
        }
        // Shift the index starting at 1 to index starting at 0
        return get((i - 1) * (2 * n + 1) + 2 * n);
    }

    uint8_t ImprovedStabilizerTableau::get_xz(uint i, uint j) {
        return (get_x(i, j) << 1) & get_z(i, j);
    }

    char ImprovedStabilizerTableau::interpret(uint8_t xz) {
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

    uint8_t ImprovedStabilizerTableau::reverse_interpret(char pauli) {
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
