#include "stabilizer_circuit.h"
#include "improved_stabilizer_tableau.h"

using namespace CliffordTableaus;

/**
 * Tasks:
 * Advanced Topics in Quantum Computing
 * - Explain Clifford Tableaus
 * - Make a Clifford Tableau
 * - Decompose Clifford Tableau
 * - Write Stabilizer Algorithm
 */
int main() {
    ImprovedStabilizerTableau stabilizerTableau = ImprovedStabilizerTableau();
    // auto final_measurement = StabilizerCircuit::interactiveMode(stabilizerTableau);
    auto final_measurement = StabilizerCircuit::executeCircuit("")
    std::cout << final_measurement << std::endl;
}