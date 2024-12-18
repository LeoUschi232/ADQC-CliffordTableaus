#include "subroutines.h"


namespace CliffordTableaus {
    int g_canonical(int x1, int z1, int x2, int z2) {
        auto x1z1 = ((x1 << 1) | z1) & 0b11;
        switch (x1z1) {
            case 0b10:
                return z2 * (2 * x2 - 1);
            case 0b11:
                return z2 - x2;
            case 0b01:
                return x2 * (1 - 2 * z2);
            default:
                return 0;
        }
    }

    int g_alternate(int x1, int z1, int x2, int z2) {
        auto x1z1 = ((x1 << 1) | z1) & 0b11;
        auto x2z2 = ((x2 << 1) | z2) & 0b11;

        // The algorithm uses a subroutine called rowsum (h, i), which sets generator h equal to i+h.
        // This means h will be set to applying the multiplication ih, not hi.
        // Therefore, we multiply x2z2*x1z1 instead of x1z1*x2z2.
        switch (x1z1) {
            case 0b10:
                // x1z1 represents the Pauli-X matrix.
                switch (x2z2) {
                    case 0b11:
                        // x2z2 represents the Pauli-Y matrix.
                        // YX=-iZ
                        // Phase factor: -i=i^{-1} => g_alternate=-1.
                        return -1;
                    case 0b01:
                        // x2z2 represents the Pauli-Z matrix.
                        // ZX=iY
                        // Phase factor: -i=i^1 => g_alternate=1.
                        return 1;
                    default:
                        // x2z2 represents the Identity matrix or the Pauli-X matrix.
                        // IX=X
                        // XX=I
                        // Phase factor: 1=i^0 => g_alternate=0.
                        return 0;
                }
            case 0b11:
                // x1z1 represents the Pauli-Y matrix.
                switch (x2z2) {
                    case 0b10:
                        // x2z2 represents the Pauli-X matrix.
                        // XY=iZ
                        // Phase factor: -i=i^1 => g_alternate=1.
                        return 1;
                    case 0b01:
                        // x2z2 represents the Pauli-Z matrix.
                        // ZY=-iX
                        // Phase factor: i=i^{-1} => g_alternate=-1.
                        return -1;
                    default:
                        // x2z2 represents the Identity matrix or the Pauli-Y matrix.
                        // IY=Y
                        // YY=I
                        // Phase factor: 1=i^0 => g_alternate=0.
                        return 0;
                }
            case 0b01:
                // x1z1 represents the Pauli-Z matrix.
                switch (x2z2) {
                    case 0b10:
                        // x2z2 represents the Pauli-X matrix.
                        // XZ=-iY
                        // Phase factor: i=i^{-1} => g_alternate=-1.
                        return -1;
                    case 0b11:
                        // x2z2 represents the Pauli-Y matrix.
                        // YZ=iX
                        // Phase factor: -i=i^1 => g_alternate=1.
                        return 1;
                    default:
                        // x2z2 represents the Identity matrix or the Pauli-Z matrix.
                        // IZ=Z
                        // ZZ=I
                        // Phase factor: 1=i^0 => g_alternate=0.
                        return 0;
                }
            default:
                // x1z1 represents the Identity matrix.
                // The identity matrix multiplied by any other matrix is the other matrix.
                // Phase factor: 1=i^0 => g_alternate=0.
                return 0;
        }
    }

    uint8_t random_bit() {
        return distribution(generator);
    }
}
