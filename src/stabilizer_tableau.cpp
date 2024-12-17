#include "stabilizer_tableau.h"

namespace CliffordTableaus {
    void StabilizerTableau::initializeTableau(uint p_n, uint p_total_bits) {
        this->n = p_n;
        this->total_bits = p_total_bits;
        this->tableau = std::vector<uint8_t>((total_bits + 7) / 8, 0);

    }

    void StabilizerTableau::PauliX(uint qubit) {
        if (qubit > n) {
            throw std::invalid_argument("Invalid qubit index.");
        }
        this->Hadamard(qubit);
        this->PauliZ(qubit);
        this->Hadamard(qubit);
    }

    void StabilizerTableau::PauliY(uint qubit) {
        if (qubit > n) {
            throw std::invalid_argument("Invalid qubit index.");
        }
        this->PauliZ(qubit);
        this->PauliX(qubit);
        this->Phase(qubit);
        this->Phase(qubit);
        this->Phase(qubit);
        this->PauliX(qubit);
        this->Phase(qubit);
        this->Phase(qubit);
        this->Phase(qubit);
        this->PauliX(qubit);
    }

    void StabilizerTableau::PauliZ(uint qubit) {
        if (qubit > n) {
            throw std::invalid_argument("Invalid qubit index.");
        }
        this->Phase(qubit);
        this->Phase(qubit);
    }
}