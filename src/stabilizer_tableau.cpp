#include "stabilizer_tableau.h"

namespace CliffordTableaus {
    void StabilizerTableau::initializeTableau(uint p_n, uint p_total_bits) {
        this->n = p_n;
        this->total_bits = p_total_bits;
        this->tableau = std::vector<uint8_t>((total_bits + 7) / 8, 0);
    }

    void StabilizerTableau::Identity(uint qubit) const {
        if (qubit == 0) {
            throw std::invalid_argument("Attempted to apply Identity with qubit = 0!");
        }
        if (qubit > n) {
            throw std::invalid_argument("Attempted to apply Identity with qubit > n!");
        }
    }

    void StabilizerTableau::PauliX(uint qubit) {
        if (qubit == 0) {
            throw std::invalid_argument("Attempted to apply Pauli-X with qubit = 0!");
        }
        if (qubit > n) {
            throw std::invalid_argument("Attempted to apply Pauli-X with qubit > n!");
        }
        this->Hadamard(qubit);
        this->PauliZ(qubit);
        this->Hadamard(qubit);
    }

    void StabilizerTableau::PauliY(uint qubit) {
        if (qubit == 0) {
            throw std::invalid_argument("Attempted to apply Pauli-Y with qubit = 0!");
        }
        if (qubit > n) {
            throw std::invalid_argument("Attempted to apply Pauli-Y with qubit > n!");
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
        if (qubit == 0) {
            throw std::invalid_argument("Attempted to apply Pauli-Z with qubit = 0!");
        }
        if (qubit > n) {
            throw std::invalid_argument("Attempted to apply Pauli-Z with qubit > n!");
        }
        this->Phase(qubit);
        this->Phase(qubit);
    }

    void StabilizerTableau::SWAP(uint qubit1, uint qubit2) {
        if (qubit1 == 0) {
            throw std::invalid_argument("Attempted to apply SWAP with qubit1 = 0!");
        }
        if (qubit1 > n) {
            throw std::invalid_argument("Attempted to apply SWAP with qubit1 > n!");
        }
        if (qubit2 == 0) {
            throw std::invalid_argument("Attempted to apply SWAP with qubit2 = 0!");
        }
        if (qubit2 > n) {
            throw std::invalid_argument("Attempted to apply SWAP with qubit2 > n!");
        }
        if (qubit1 == qubit2) {
            return;
        }
        this->CNOT(qubit1, qubit2);
        this->CNOT(qubit2, qubit1);
        this->CNOT(qubit1, qubit2);
    }
}