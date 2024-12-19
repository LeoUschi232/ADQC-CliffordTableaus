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
        void initializeTableau(uint p_n, uint p_total_bits);

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

        /**
         * Apply the Identity gate to the qubit.
         * @param qubit Qubit to apply the Identity gate to.
         */
        void Identity(uint qubit) const;

        /**
         * Apply the Pauli X gate to the qubit via decomposition of X using Hadamard and Phase gates.
         * @param qubit Qubit to apply the Pauli-X gate to.
         */
        void PauliX(uint qubit);

        /**
         * Apply the Pauli Y gate to the qubit via decomposition of Y using Hadamard and Phase gates.
         * @param qubit Qubit to apply the Pauli-Y gate to.
         */
        void PauliY(uint qubit);

        /**
         * Apply the Pauli Z gate to the qubit via decomposition of Z using Phase gates.
         * @param qubit Qubit to apply the Pauli-Z gate to.
         */
        void PauliZ(uint qubit);

        /**
         * Apply the SWAP gate to the qubits qubit1 and qubit2.
         * @param qubit1 Qubit to swap with qubit2.
         * @param qubit2 Qubit to swap with qubit1.
         */
        void SWAP(uint qubit1, uint qubit2);
    };
}