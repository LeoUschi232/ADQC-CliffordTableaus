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
    StabilizerCircuit::interactiveMode(stabilizerTableau);
}