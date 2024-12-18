from matplotlib import pyplot as plt  # for: subplots, colorbar, cm, show
from matplotlib.cm import ScalarMappable
from colorama import Fore, Style
from functools import reduce
from SimulatorVisitor import *
from openqasm3 import ast
from numpy import *
from numpy import isclose
from numpy.linalg import norm

# Some useful global variables
inverse_sqrt2 = 0.7071067811865475
identity_2d = eye(2)
x_pauli_gate = array([[0, 1], [1, 0]])
y_pauli_gate = array([[0, -1j], [1j, 0]])
z_pauli_gate = array([[1, 0], [0, -1]])
hadamard_gate = array([[inverse_sqrt2, inverse_sqrt2], [inverse_sqrt2, -inverse_sqrt2]])
phase_gate = array([[1, 0], [0, 1j]])
t_gate = array([[1, 0], [0, exp(0.25j * pi)]])
m0 = array([[1, 0], [0, 0]])
m1 = array([[0, 0], [0, 1]])


class Simulator(SimulatorVisitor):
    def __init__(self):
        self.n_qubits = 0
        self.n_possible_states = None
        self.statevector = None
        self.qubit_range = None
        self.use_optimized = False
        self.use_control_optimized = False
        self.use_double_control_optimized = False

    def set_use_optimized(
            self,
            use_optimized: bool = True,
            use_control_optimized: bool = True,
            use_double_control_optimized: bool = True
    ):
        self.use_optimized = use_optimized
        self.use_control_optimized = use_control_optimized
        self.use_double_control_optimized = use_double_control_optimized

    def simulate(self, ast_param: ast.QASMNode):
        self.visit(ast_param)

    def initStatevector(self, n_qubits: int):
        self.n_qubits = n_qubits
        self.n_possible_states = 2 ** self.n_qubits
        self.statevector = zeros(self.n_possible_states, dtype=complex)
        self.statevector[0] = 1
        self.qubit_range = range(n_qubits)

    def get_statevector(self):
        # Return a copy of the state vector rather than the original
        return array([complex(state_amplitude) for state_amplitude in self.statevector], dtype=complex)

    def apply_gate(self, target: int, gate: ndarray):
        # Handle invalid inputs
        if not 0 <= target < self.n_qubits:
            raise RuntimeError("Target qubit index out of range!")

        # If the simulation is set to use optimized computation, do so instead.
        if self.use_optimized:
            self.apply_gate_optimized(target, gate)
            return

        matrices = [gate if q == target else identity_2d for q in range(self.n_qubits)][::-1]
        self.statevector = reduce(kron, matrices) @ array(self.statevector)

    def x(self, target: int, param: Optional[float]):
        self.apply_gate(target, x_pauli_gate)

    def y(self, target: int, param: Optional[float]):
        self.apply_gate(target, y_pauli_gate)

    def z(self, target: int, param: Optional[float]):
        self.apply_gate(target, z_pauli_gate)

    def h(self, target: int, param: Optional[float]):
        self.apply_gate(target, hadamard_gate)

    def s(self, target: int, param: Optional[float]):
        self.apply_gate(target, phase_gate)

    def t(self, target: int, param: Optional[float]):
        self.apply_gate(target, t_gate)

    def rx(self, target: int, param: Optional[float]):
        if param is None:
            param = 0
        cos_param = cos(0.5 * param)
        sin_param = -1j * sin(0.5 * param)
        rx_gate = array([[cos_param, sin_param], [sin_param, cos_param]])
        self.apply_gate(target, rx_gate)

    def ry(self, target: int, param: Optional[float]):
        if param is None:
            param = 0
        sin_param = sin(0.5 * param)
        cos_param = cos(0.5 * param)
        ry_gate = array([[cos_param, -sin_param], [sin_param, cos_param]])
        self.apply_gate(target, ry_gate)

    def rz(self, target: int, param: Optional[float]):
        if param is None:
            param = 0
        rz_gate = array([[exp(-0.5j * param), 0], [0, exp(0.5j * param)]])
        self.apply_gate(target, rz_gate)

    def apply_control_gate(self, control: int, target: int, gate: ndarray):
        # Handle invalid inputs
        if not 0 <= target < self.n_qubits or not 0 <= control < self.n_qubits or target == control:
            raise RuntimeError("Invalid input to the control gate!")

        # If the simulation is set to use optimized computation, do so instead.
        if self.use_control_optimized:
            self.apply_control_gate_optimized(control, target, gate)
            return

        # Build the matrices for each qubit position
        left_control = [
            m0 if qubit == control
            else identity_2d for qubit in self.qubit_range
        ]
        left_control = left_control[::-1]
        right_control = [
            m1 if qubit == control
            else gate if qubit == target
            else identity_2d for qubit in self.qubit_range
        ]
        right_control = right_control[::-1]

        # Compute the full control gate by summing the two tensor products
        full_control_gate = reduce(kron, left_control) + reduce(kron, right_control)
        self.statevector = full_control_gate @ array(self.statevector)

    def cx(self, control: int, target: int, param: Optional[float] = None):
        self.apply_control_gate(control, target, x_pauli_gate)

    def cy(self, control: int, target: int, param: Optional[float] = None):
        self.apply_control_gate(control, target, y_pauli_gate)

    def cz(self, control: int, target: int, param: Optional[float] = None):
        self.apply_control_gate(control, target, z_pauli_gate)

    def ch(self, control: int, target: int, param: Optional[float] = None):
        self.apply_control_gate(control, target, hadamard_gate)

    def cs(self, control: int, target: int, param: Optional[float] = None):
        self.apply_control_gate(control, target, phase_gate)

    def ct(self, control: int, target: int, param: Optional[float] = None):
        self.apply_control_gate(control, target, t_gate)

    def apply_double_control_gate(self, control1: int, control2: int, target: int, gate: ndarray):
        # Handle invalid inputs
        if not 0 <= target < self.n_qubits or not 0 <= control1 < self.n_qubits or not 0 <= control2 < self.n_qubits \
                or target == control1 or control1 == control2 or control2 == target:
            raise RuntimeError("Invalid input to the double control gate!")

        # If the simulation is set to use optimized computation, do so instead.
        if self.use_double_control_optimized:
            self.apply_double_control_gate_optimized(control1, control2, target, gate)
            return

        # Map the control states to their corresponding matrix components
        submatrices = {
            "00": [m0 if q in [control1, control2] else identity_2d for q in self.qubit_range][::-1],
            "01": [m0 if q == control1 else m1 if q == control2 else identity_2d for q in self.qubit_range][::-1],
            "10": [m1 if q == control1 else m0 if q == control2 else identity_2d for q in self.qubit_range][::-1],
            "11": [m1 if q in [control1, control2] else gate if q == target
            else identity_2d for q in self.qubit_range][::-1],
        }

        # Sum the tensor products for each control state
        full_control_gate = sum(reduce(kron, component) for component in submatrices.values())
        self.statevector = full_control_gate @ self.statevector

    def ccx(self, control1: int, control2: int, target: int, param: Optional[float]):
        self.apply_double_control_gate(control1, control2, target, x_pauli_gate)

    def ccy(self, control1: int, control2: int, target: int, param: Optional[float]):
        self.apply_double_control_gate(control1, control2, target, y_pauli_gate)

    def ccz(self, control1: int, control2: int, target: int, param: Optional[float]):
        self.apply_double_control_gate(control1, control2, target, z_pauli_gate)

    def cch(self, control1: int, control2: int, target: int, param: Optional[float]):
        self.apply_double_control_gate(control1, control2, target, hadamard_gate)

    def ccs(self, control1: int, control2: int, target: int, param: Optional[float]):
        self.apply_double_control_gate(control1, control2, target, phase_gate)

    def cct(self, control1: int, control2: int, target: int, param: Optional[float]):
        self.apply_double_control_gate(control1, control2, target, t_gate)

    def measure(self, qubit: int, param: Optional[float] = None):
        # Handle invalid qubit input
        if qubit < 0 or qubit >= self.n_qubits:
            raise RuntimeError("Qubit index out of range!")

        # Create a measurement matrix for each of the 2^n possible multi-qubit states
        measurement_matrices = [
            [m0 if q == qubit else identity_2d for q in self.qubit_range],
            [m1 if q == qubit else identity_2d for q in self.qubit_range]
        ]

        # Do not collapse all lists of possible measurements into usable n-state matrices
        # Instead, locally create and replace the currently used measurement matrix at each point.
        # This should theoretically conserve available resources.
        outcome_state_probabilities = []
        possible_outcome_states = []
        for measurement_matrix in measurement_matrices:
            compound_measurement_matrix = reduce(kron, measurement_matrix)
            unnormalized_state = compound_measurement_matrix @ array(self.statevector)
            state_norm = norm(unnormalized_state)
            if isclose(state_norm, 0.0, rtol=1e-12):
                continue

            # Add the probability of the outcome state and the normalized state
            # to the corresponding lists for later drawing of lots.
            outcome_state_probabilities.append(state_norm * state_norm)
            possible_outcome_states.append(unnormalized_state / state_norm)

        # Make sure that all outcome state probabilities sum up to roughly one.
        # Afterward perform the drawing of the lots!
        osp_sum = sum(outcome_state_probabilities)
        if not isclose(osp_sum, 1.0, rtol=1e-9):
            print(Fore.YELLOW + "WARNING: Outcome state probabilities do not sum up to 1.0!" + Style.RESET_ALL)
            print(f"Sum of Outcome state probabilities: {osp_sum}\n")
        state_index = random.choice(range(len(outcome_state_probabilities)), p=outcome_state_probabilities)
        self.statevector = possible_outcome_states[state_index]

    def apply_gate_optimized(self, target: int, gate: ndarray):
        # The bitstring in the ket which represents the multi-qubit state is in the reverse order to a binary number.
        # That's why the location of the target qubit in the state's bitarray has to be considered
        # from left to right instead of from right to left.
        target_location = 2 ** target

        for state1 in range(self.n_possible_states):
            # For each state where the target qubit is 0, compute the corresponding state
            # with all other qubits the same but the target qubit 1.
            # &: bitwise-AND
            # ^: bitwise-XOR
            if state1 & target_location == 0:
                state2 = state1 ^ target_location

                # Perform the unitary operation of the corresponding gate like explained in the exercise.
                alpha1 = self.statevector[state1]
                beta1 = self.statevector[state2]
                alpha2, beta2 = gate @ array([alpha1, beta1])
                self.statevector[state1] = alpha2
                self.statevector[state2] = beta2

    def apply_control_gate_optimized(self, control: int, target: int, gate: ndarray):
        # The bitstring in the ket which represents the multi-qubit state is in the reverse order to a binary number.
        # That's why the location of the target qubit in the state's bitarray has to be considered
        # from left to right instead of from right to left.
        control_location = 2 ** control
        target_location = 2 ** target

        for state1 in range(self.n_possible_states):
            # For each state where the target qubit is 0, compute the corresponding state
            # with all other qubits the same but the target qubit 1.
            # &: bitwise-AND
            # ^: bitwise-XOR
            # Same logic as for single-qubit gates but this time with double the amount of states.
            if state1 & control_location == 0 and state1 & target_location == 0:
                state2 = state1 ^ target_location
                state3 = state1 ^ control_location
                state4 = state2 ^ control_location

                a1 = self.statevector[state1]
                b1 = self.statevector[state2]
                c1 = self.statevector[state3]
                d1 = self.statevector[state4]

                compound_state = array([a1, b1, c1, d1])
                compound_gate = kron(m0, identity_2d) + kron(m1, gate)
                a2, b2, c2, d2 = compound_gate @ compound_state

                self.statevector[state1] = a2
                self.statevector[state2] = b2
                self.statevector[state3] = c2
                self.statevector[state4] = d2

    def apply_double_control_gate_optimized(self, control1: int, control2: int, target: int, gate: ndarray):
        # Same logic as for the single-qubit control gates but expanded onto 2-qubit control
        control1_location = 2 ** control1
        control2_location = 2 ** control2
        target_location = 2 ** target

        for s1 in range(self.n_possible_states):
            if s1 & control1_location == 0 and s1 & control2_location == 0 and s1 & target_location == 0:
                s2 = s1 ^ target_location
                s3 = s1 ^ control1_location
                s4 = s2 ^ control1_location
                s5 = s1 ^ control2_location
                s6 = s2 ^ control2_location
                s7 = s3 ^ control2_location
                s8 = s4 ^ control2_location

                states = [s1, s2, s3, s4, s5, s6, s7, s8]
                compound_state = array([self.statevector[state] for state in states])
                compound_gate = (
                        reduce(kron, [m0, m0, identity_2d])
                        + reduce(kron, [m0, m1, identity_2d])
                        + reduce(kron, [m1, m0, identity_2d])
                        + reduce(kron, [m1, m1, gate])
                )
                new_amplitudes = compound_gate @ compound_state

                for state, amplitude in zip(states, new_amplitudes):
                    self.statevector[state] = amplitude

    def visualize(self):
        if plt is None:
            print("Pyplot is None. Nothing to visualize")
            return

        kets = []
        probabilities = []
        phases = []

        for state in range(self.n_possible_states):
            state_amplitude = abs(self.statevector[state])
            if not isclose(state_amplitude, 0.0, rtol=1e-12):
                kets.append(f"|{state:0{self.n_qubits}b}⟩")
                probabilities.append(state_amplitude ** 2)
                phases.append(angle(self.statevector[state]))

        # Create a color-coding for the phases of the qubits
        color_map = "twilight_shifted"
        color_function = getattr(plt.cm, color_map)
        colors = [color_function((phase + pi) / (2 * pi)) for phase in phases]
        sm = ScalarMappable(cmap=color_map)
        sm.set_array([-pi, pi])

        # Paint the plot using the color code
        fig, ax = plt.subplots()
        bars = ax.bar(range(len(kets)), probabilities, color=colors, tick_label=kets)
        cbar = plt.colorbar(sm, ax=ax, label="Phase [Rad]")
        ax.tick_params(axis="x", rotation=90)
        ax.set_ylabel("Probability")
        ax.set_xlabel("State part")

        # Expand the bottom of the figure so the kets don't get cut off
        fig.tight_layout()
        fig.show()
