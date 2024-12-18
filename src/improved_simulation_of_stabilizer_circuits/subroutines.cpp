#include "subroutines.h"


namespace CliffordTableaus {


    int matrix_interpret_multiply_interpret(int r1, int x1, int z1, int r2, int x2, int z2){
        auto matrix_multiplication_code = (r1 << 5) | (x1 << 4) | (z1 << 3) | (r2 << 2) | (x2 << 1) | z2;
        switch (matrix_multiplication_code) {
            case 0b000000:
                // II=I => 0b000
                return 0b000;
        }
    }




    int g(int x1, int z1, int x2, int z2) {
        auto x1z1 = ((x1 << 1) | z1) & 0b11;
        auto x2z2 = ((x2 << 1) | z2) & 0b11;
        switch (x1z1) {
            case 0b10:
                // x1z1 represents the Pauli-X matrix.
                switch (x2z2) {
                    case 0b11:
                        // x2z2 represents the Pauli-Y matrix.
                        // XY=iZ
                        // Phase factor: i=i^1 => g=1.
                        return 1;
                    case 0b01:
                        // x2z2 represents the Pauli-Z matrix.
                        // XZ=-iY
                        // Phase factor: -i=i^{-1} => g=-1.
                        return -1;
                    default:
                        // x2z2 represents the Identity matrix or the Pauli-X matrix.
                        // XI=X
                        // XX=I
                        // Phase factor: 1=i^0 => g=0.
                        return 0;
                }
            case 0b11:
                // x1z1 represents the Pauli-Y matrix.
                switch (x2z2) {
                    case 0b10:
                        // x2z2 represents the Pauli-X matrix.
                        // YX=-iZ
                        // Phase factor: -i=i^{-1} => g=-1.
                        return -1;
                    case 0b01:
                        // x2z2 represents the Pauli-Z matrix.
                        // YZ=iX
                        // Phase factor: i=i^1 => g=1.
                        return 1;
                    default:
                        // x2z2 represents the Identity matrix or the Pauli-Y matrix.
                        // YI=Y
                        // YY=I
                        // Phase factor: 1=i^0 => g=0.
                        return 0;
                }
            case 0b01:
                // x1z1 represents the Pauli-Z matrix.
                switch (x2z2) {
                    case 0b10:
                        // x2z2 represents the Pauli-X matrix.
                        // ZX=iY
                        // Phase factor: i=i^1 => g=1.
                        return 1;
                    case 0b11:
                        // x2z2 represents the Pauli-Y matrix.
                        // ZY=-iX
                        // Phase factor: -i=i^{-1} => g=-1.
                        return -1;
                    default:
                        // x2z2 represents the Identity matrix or the Pauli-Z matrix.
                        // ZI=Z
                        // ZZ=I
                        // Phase factor: 1=i^0 => g=0.
                        return 0;
                }
            default:
                // x1z1 represents the Identity matrix.
                // The identity matrix multiplied by any other matrix is the other matrix.
                // Phase factor: 1=i^0 => g=0.
                return 0;
        }
    }

    uint8_t random_bit() {
        return distribution(generator);
    }
}
