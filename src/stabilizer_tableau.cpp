#include "stabilizer_tableau.h"

namespace CliffordTableaus {
    void StabilizerTableau::initializeTableau(uint p_n, uint p_total_bits) {
        this->n = p_n;
        this->total_bits = p_total_bits;
        this->tableau = std::vector<uint8_t>((total_bits + 7) / 8, 0);
    }

    void StabilizerTableau::Identity(uint qubit) const {
        if (qubit == 0) {
            std::cerr << "Warning: Attempted to apply Identity with qubit = 0!" << std::endl;
            return;
        }
        if (qubit > n) {
            std::cerr << "Warning: Attempted to apply Identity with qubit > n!" << std::endl;
            return;
        }
    }

    void StabilizerTableau::PauliX(uint qubit) {
        if (qubit == 0) {
            std::cerr << "Warning: Attempted to apply Pauli-X with qubit = 0!" << std::endl;
            return;
        }
        if (qubit > n) {
            std::cerr << "Warning: Attempted to apply Pauli-X with qubit > n!" << std::endl;
            return;
        }
        this->Hadamard(qubit);
        this->PauliZ(qubit);
        this->Hadamard(qubit);
    }

    void StabilizerTableau::PauliY(uint qubit) {
        if (qubit == 0) {
            std::cerr << "Warning: Attempted to apply Pauli-Y with qubit = 0!" << std::endl;
            return;
        }
        if (qubit > n) {
            std::cerr << "Warning: Attempted to apply Pauli-Y with qubit > n!" << std::endl;
            return;
        }
        this->Phase(qubit);
        this->PauliX(qubit);
        this->Phase(qubit);
        this->Phase(qubit);
        this->Phase(qubit);
    }

    void StabilizerTableau::PauliZ(uint qubit) {
        if (qubit == 0) {
            std::cerr << "Warning: Attempted to apply Pauli-Z with qubit = 0!" << std::endl;
            return;
        }
        if (qubit > n) {
            std::cerr << "Warning: Attempted to apply Pauli-Z with qubit > n!" << std::endl;
            return;
        }
        this->Phase(qubit);
        this->Phase(qubit);
    }

    void StabilizerTableau::SWAP(uint qubit1, uint qubit2) {
        if (qubit1 == 0) {
            std::cerr << "Attempted to apply SWAP with qubit1 = 0!" << std::endl;
            return;
        }
        if (qubit1 > n) {
            std::cerr << "Attempted to apply SWAP with qubit1 > n!" << std::endl;
            return;
        }
        if (qubit2 == 0) {
            std::cerr << "Attempted to apply SWAP with qubit2 = 0!" << std::endl;
            return;
        }
        if (qubit2 > n) {
            std::cerr << "Attempted to apply SWAP with qubit2 > n!" << std::endl;
            return;
        }
        if (qubit1 == qubit2) {
            return;
        }
        this->CNOT(qubit1, qubit2);
        this->CNOT(qubit2, qubit1);
        this->CNOT(qubit1, qubit2);
    }
}