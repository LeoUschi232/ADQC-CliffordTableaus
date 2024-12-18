########################################################################################################################
matplotlib_found = True
try:
    from matplotlib import pyplot as plt
    from matplotlib.gridspec import GridSpec
except ImportError as error:
    print(error)
    plt = None
    GridSpec = None
    matplotlib_found = False
########################################################################################################################
from sys import path
from re import sub
from numpy import array, log2, ndarray
from itertools import product


def get_bitstrings(length: int):
    return ["".join(bits) for bits in product("01", repeat=length)]


def get_states(length: int):
    return [f"|{bitstring}⟩" for bitstring in get_bitstrings(length)]


def get_probabilities_from_counts(p_counts: dict):
    all_bitstrings = get_bitstrings(length=len(list(p_counts.keys())[0]))
    total_counts = sum(list(p_counts.values()))
    full_probabilities = {bitstring: p_counts.get(bitstring, 0) / total_counts for bitstring in all_bitstrings}
    return dict(sorted(full_probabilities.items()))


def get_probabilities_from_statevector(statevector: ndarray):
    bitstrings = get_bitstrings(length=round(log2(len(statevector))))
    states = [f"|{bitstring}⟩" for bitstring in bitstrings]
    return {
        state: abs(state_amplitude) ** 2
        for state, state_amplitude in zip(states, statevector)
    }


def visualize_probabilities(
        probs_1_name: str,
        probs_1_dict: dict,
        probs_2_name: str,
        probs_2_dict: dict,
        p_plot_style: int,
        plot_title: str = "Probability distribution comparison"
):
    if matplotlib_found:
        if p_plot_style == 1:
            visualize_probabilities_style_1(probs_1_name, probs_1_dict, probs_2_name, probs_2_dict)
        elif p_plot_style == 2:
            visualize_probabilities_style_2(probs_1_name, probs_1_dict, probs_2_name, probs_2_dict, plot_title)


def visualize_probabilities_style_1(
        probs_1_name: str,
        probs_1_dict: dict,
        probs_2_name: str,
        probs_2_dict: dict
):
    if len(probs_1_dict) != len(probs_2_dict):
        raise RuntimeError("Probability distributions have different lengths!")

    n_possible_states = len(probs_1_dict)
    n_qubits = round(log2(n_possible_states))

    fig = plt.figure(figsize=(14, 12))
    gs = GridSpec(2, 1, figure=fig)

    ax1 = fig.add_subplot(gs[0, 0])
    ax1.grid(True, zorder=0)
    ax1.bar(
        range(n_possible_states),
        array(list(probs_1_dict.values())),
        tick_label=probs_1_dict.keys(),
        zorder=2
    )
    ax1.set_title(str(probs_1_name))
    ax1.tick_params(axis="x", rotation=90)
    ax1.set_ylabel("Probability")
    ax1.set_xlabel("State")

    ax2 = fig.add_subplot(gs[1, 0])
    ax2.grid(True, zorder=0)
    ax2.bar(
        range(n_possible_states),
        array(list(probs_2_dict.values())),
        tick_label=probs_2_dict.keys(),
        zorder=2
    )
    ax2.set_title(str(probs_2_name))
    ax2.tick_params(axis="x", rotation=90)
    ax2.set_ylabel("Probability")
    ax2.set_xlabel("State")

    fig.tight_layout()
    fig.show()


def visualize_probabilities_style_2(
        probs_1_name: str,
        probs_1_dict: dict,
        probs_2_name: str,
        probs_2_dict: dict,
        plot_title: str = "Probability distribution comparison"
):
    if len(probs_1_dict) != len(probs_2_dict):
        raise RuntimeError("Probability distributions have different lengths!")

    n_possible_states = len(probs_1_dict)
    state_labels = list(probs_1_dict.keys())
    values1 = array(list(probs_1_dict.values()))
    values2 = array(list(probs_2_dict.values()))

    fig = plt.figure(figsize=(14, 8))
    gs = GridSpec(1, 1, figure=fig)
    ax = fig.add_subplot(gs[0, 0])

    bar_width = 0.4
    indices = range(n_possible_states)

    ax.bar(
        [i - bar_width / 2 for i in indices],
        values1,
        width=bar_width,
        color="orange",
        label=str(probs_1_name)
    )
    ax.bar(
        [i + bar_width / 2 for i in indices],
        values2,
        width=bar_width,
        color="green",
        label=str(probs_2_name)
    )

    ax.set_title(plot_title)
    ax.set_xticks(indices)
    ax.set_xticklabels(state_labels, rotation=90)
    ax.set_ylabel("Probability")
    ax.set_xlabel("State")
    ax.grid(True, zorder=-1)
    ax.legend()

    fig.tight_layout()
    fig.show()


def get_custom_simulation_circuit(qc_dump: str):
    try:
        from openqasm3 import parse
        path.insert(0, "../../../assignment02/src/qc-simulation")
        # noinspection PyUnresolvedReferences
        from SimulatorTemplate import Simulator as CustomSimulator
    except ImportError as import_error:
        print(import_error)
        return None

    qasm3_code = sub(r"gate\s+ccz\s+_gate_q_\d+,\s*_gate_q_\d+,\s*_gate_q_\d+\s*{[^}]*}\n", "", qc_dump)
    custom_simulator = CustomSimulator()
    custom_simulator.set_use_optimized()
    custom_simulator.simulate(parse(qasm3_code))
    return get_probabilities_from_statevector(statevector=custom_simulator.get_statevector())


if __name__ == "__main__":
    quantum_hardware_name = "Q5"
    hardcoded_real_probabilities = None
    hardcoded_qc_dump = None

    visualize_probabilities(
        probs_1_name="Simulator",
        probs_1_dict=get_custom_simulation_circuit(hardcoded_qc_dump),
        probs_2_name=quantum_hardware_name,
        probs_2_dict=hardcoded_real_probabilities,
        p_plot_style=2
    )
