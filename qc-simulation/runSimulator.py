from openqasm3 import parse
from SimulatorTemplate import Simulator
from qiskit.qasm3 import loads
from qiskit_aer import Aer
from numpy import abs, log2
import warnings

warnings.filterwarnings("ignore", category=DeprecationWarning)

filepath = "zMainCircuits/test_circuit_9.qasm"

with open(filepath, "r") as program:
    qasm_code = program.read()

    qc = loads(qasm_code)
    backend = Aer.get_backend("statevector_simulator")
    job = backend.run(qc)
    result = job.result()

    statevector = result.get_statevector()
    n_qubits = int(log2(len(statevector)))
    states_and_probabilities = {
        f"{index:0{n_qubits}b}"[::-1]: round(float(abs(amplitude) ** 2), 7)
        for index, amplitude in enumerate(statevector)
        if abs(amplitude) ** 2 > 1e-12
    }
    for key in states_and_probabilities.keys():
        print(key)

    qasm_code = qasm_code.replace("include \"stdgates.inc\";\n", "")
    ast = parse(qasm_code)
    sim = Simulator()
    sim.set_use_optimized()
    sim.simulate(ast)
    sim.visualize()
