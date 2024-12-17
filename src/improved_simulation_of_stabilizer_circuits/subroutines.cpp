#include "subroutines.h"


namespace CliffordTableaus {
    int g(int x1, int z1, int x2, int z2) {
        switch ((x1 << 1) | z1) {
            case 0b00:
                return 0;
            case 0b11:
                return z2 - x2;
            case 0b10:
                return z2 * (2 * x2 - 1);
            case 0b01:
                return x2 * (1 - 2 * z2);
            default:
                throw std::invalid_argument("Invalid input to the g-function.");
        }
    }

    uint8_t random_bit() {
        return distribution(generator);
    }
}
