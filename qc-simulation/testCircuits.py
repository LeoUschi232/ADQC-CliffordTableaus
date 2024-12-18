from unittest import TestCase
from openqasm3 import parse
from SimulatorTemplate import Simulator
from matplotlib.pyplot import cm, show, figure
from matplotlib.cm import ScalarMappable
from matplotlib.gridspec import GridSpec
from numpy import *
from numpy import isclose


class TestOptimization(TestCase):
    def test_circuit(self, test_circuit_path: str = None):
        if test_circuit_path is None:
            return
        with open(test_circuit_path, "r") as program:
            ast = parse(program.read())

            # Unoptimized run-through
            sim = Simulator()
            sim.simulate(ast)
            unoptimized_statevector = sim.get_statevector()

            # Optimized run-through
            sim = Simulator()
            sim.set_use_optimized()
            sim.simulate(ast)
            optimized_statevector = sim.get_statevector()

            # Compare the vectors to see if they all resulted in the same values
            test_passed = isclose(unoptimized_statevector, optimized_statevector).all()
            if not test_passed:
                self.visualize(unoptimized_statevector, optimized_statevector, test_circuit_path)
            self.assertTrue(test_passed, msg=f"Optimization failed on test file: {test_circuit_path}")

    def test_circuit1(self):
        self.test_circuit(test_circuit_path="unitTestCircuits/testCircuit1.qasm")

    def test_circuit2(self):
        self.test_circuit(test_circuit_path="unitTestCircuits/testCircuit2.qasm")

    def test_circuit3(self):
        self.test_circuit(test_circuit_path="unitTestCircuits/testCircuit3.qasm")

    def test_circuit4(self):
        self.test_circuit(test_circuit_path="unitTestCircuits/testCircuit4.qasm")

    def test_circuit5(self):
        self.test_circuit(test_circuit_path="unitTestCircuits/testCircuit5.qasm")

    def test_circuit6(self):
        self.test_circuit(test_circuit_path="unitTestCircuits/testCircuit6.qasm")

    def test_circuit7(self):
        self.test_circuit(test_circuit_path="unitTestCircuits/testCircuit7.qasm")

    def test_circuit8(self):
        self.test_circuit(test_circuit_path="unitTestCircuits/testCircuit8.qasm")

    def test_circuit9(self):
        self.test_circuit(test_circuit_path="unitTestCircuits/testCircuit9.qasm")

    def visualize(self, unoptimized_statevector, optimized_statevector, filepath):
        if len(unoptimized_statevector) != len(optimized_statevector):
            self.fail("Vectors have different lengths!")
        plot_title = f"Test Circuit {filepath[28:-5]}"

        n_possible_states = len(unoptimized_statevector)
        n_qubits = round(log2(n_possible_states)).astype(int)

        def extract_plot_data(statevector):
            kets = []
            probabilities = []
            phases = []
            for state in range(len(statevector)):
                state_amplitude = abs(statevector[state])
                if not isclose(state_amplitude, 0.0, rtol=1e-12):
                    kets.append(f"|{state:0{n_qubits}b}⟩")
                    probabilities.append(state_amplitude ** 2)
                    phases.append(angle(statevector[state]))
            return kets, probabilities, phases

        unoptimized_kets, unoptimized_probabilities, unoptimized_phases = extract_plot_data(unoptimized_statevector)
        optimized_kets, optimized_probabilities, optimized_phases = extract_plot_data(optimized_statevector)

        # Create color mapping for phase
        color_map = "twilight_shifted"
        color_function = getattr(cm, color_map)
        unoptimized_colors = [color_function((phase + pi) / (2 * pi)) for phase in unoptimized_phases]
        optimized_colors = [color_function((phase + pi) / (2 * pi)) for phase in optimized_phases]
        sm = ScalarMappable(cmap=color_map)
        sm.set_array([-pi, pi])
        fig = figure(figsize=(14, 12))
        gs = GridSpec(2, 2, width_ratios=[0.95, 0.05], height_ratios=[1, 1], figure=fig)

        # Unoptimized state vector plot
        ax1 = fig.add_subplot(gs[0, 0])
        ax1.bar(
            range(len(unoptimized_kets)),
            unoptimized_probabilities,
            color=unoptimized_colors,
            tick_label=unoptimized_kets
        )
        ax1.set_title("Unoptimized Statevector")
        ax1.tick_params(axis="x", rotation=90)
        ax1.set_ylabel("Probability")
        ax1.set_xlabel("State part")

        # Optimized state vector plot
        ax2 = fig.add_subplot(gs[1, 0])
        ax2.bar(
            range(len(optimized_kets)),
            optimized_probabilities,
            color=optimized_colors,
            tick_label=optimized_kets
        )
        ax2.set_title("Optimized Statevector")
        ax2.tick_params(axis="x", rotation=90)
        ax2.set_xlabel("State part")

        cbar_ax = fig.add_subplot(gs[:, 1])
        fig.colorbar(sm, cax=cbar_ax, label="Phase [Rad]")
        fig.suptitle(plot_title)
        fig.tight_layout()
        show()
