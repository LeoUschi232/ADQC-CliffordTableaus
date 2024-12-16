
#include "subroutines.h"

#include <stdexcept>

namespace CliffordTableaus {
    int g(int x1z1x2z2) {
        x1z1x2z2 &= 0b1111;
        int x1z1 = x1z1x2z2 >> 2;
        int x2 = (x1z1x2z2 & 0b10) >> 1;
        int z2 = x1z1x2z2 & 0b1;
        switch (x1z1) {
            case 0b00:
                return 0;
            case 0b11:
                return z2 - x2;
            case 0b10:
                return z2 * (2 * x2 - 1);
            case 0b01:
                return x2 * (1 - 2 * z2);
            default:
                throw std::invalid_argument("Invalid input.");
        }
    }

    int rowsum(int h, int i){

    }

}
