#include "subroutines.h"


namespace CliffordTableaus {
    int g(int x1, int z1, int x2, int z2) {
        auto x1z1 = ((x1 << 1) | z1) & 0b11;
        switch (x1z1) {
            case 0b11:
                return z2 - x2;
            case 0b10:
                return z2 * (2 * x2 - 1);
            case 0b01:
                return x2 * (1 - 2 * z2);
            default:
                return 0;
        }
    }

    uint8_t random_bit() {
        return distribution(generator);
    }
}
