from openqasm3 import parse
from SimulatorTemplate import Simulator

filepath = "testCircuits/bernstein_16.qasm"

with open(filepath, "r") as program:
    ast = parse(program.read())
    sim = Simulator()
    sim.set_use_optimized()
    sim.simulate(ast)
    sim.visualize()
