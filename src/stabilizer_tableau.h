#pragma once

#include <cstdint>
#include <stdexcept>
#include <cstdint>
#include <vector>


namespace CliffordTableaus {
    using uint = std::size_t;

    class StabilizerTableau {
    protected:
        /**
         * The number of qubits in the system.
         */
        uint n{};

        /**
         * The total number of bits needed to specify the state.
         * Also total number of bits in the tableau.
         */
        uint total_bits{};

        /**
         * The tableau of stabilizer and destabilizer generators.
         * The destabilizer generators occupy the first n rows of the tableau.
         * The stabilizer generators occupy the next n rows.
         * It is convenient to add an additional (2n+1)-st row for scratch space.
         * Therefore the tableau is (2n+1)x(2n+1) big.
         */
        std::vector<uint8_t> tableau;

        /**
         * Default Constructor exclusively for the subclasses.
         */
        explicit StabilizerTableau() = default;

        /**
        * Initialize the tableau with the given number of qubits and total bits.
        * @param p_n Number of qubits in the system.
        * @param p_total_bits Number of bits necessary to specify the state using the tableau.
        */
        virtual inline void initializeTableau(uint p_n, uint p_total_bits) {
            this->n = p_n;
            this->total_bits = p_total_bits;
            this->tableau = std::vector<uint8_t>((total_bits + 7) / 8, 0);
        }

    public:
        /**
         * Initialize the tableau with the given number of qubits.
         * The overriding subclass must determine the amount of necessary total_bits from the amount of qubits
         * and call the protected method initializeTableau with 2 arguments appropriately.
         * @param p_n Number of qubits in the system.
         */
        virtual void initializeTableau(uint p_n) = 0;

        /**
         * Virtual Destructor.
         */
        virtual ~StabilizerTableau() = default;

        /**
         * Transform the tableau according to the CNOT gate applied to qubits control and target.
         * After application the tableau stabilizes the state |ψ〉→ CNOT(control, target)|ψ〉.
         * @param control Control qubit a.
         * @param target Target qubit b.
         */
        virtual void CNOT(uint control, uint target) = 0;

        /**
         * Transform the tableau according to the Hadamard gate applied to the qubit qubit.
         * After application the tableau stabilizes the state |ψ〉→ H(qubit)|ψ〉.
         * @param qubit Qubit to apply the Hadamard gate to.
         */
        virtual void Hadamard(uint qubit) = 0;

        /**
         * Transform the tableau according to the Phase gate applied to the qubit qubit.
         * After application the tableau stabilizes the state |ψ〉→ Phase(qubit)|ψ〉.
         * @param qubit Qubit to apply the Phase gate to.
         */
        virtual void Phase(uint qubit) = 0;

        /**
         * Transform the tableau according to a measurement performed on qubit given by qubit.
         * @param qubit Qubit to measure.
         * @return The measurement outcome.
         */
        virtual uint8_t Measurement(uint qubit) = 0;
    };
}