from openqasm3 import parse
from SimulatorTemplate import Simulator

debug_program = """
OPENQASM 3;
qreg q[2];
rz(-1) q[0];
rz(-0.5) q[1];
"""

alpha = 0
beta = 0
subtask = input("Subtask a|b|c?").strip()
if subtask not in ["a", "b", "c"]:
    subtask = "d"
if subtask == "c":
    print("Expected format of input: int | float | (int|float)*pi | pi/(int|float) | (int|float)*pi/(int|float)")
    alpha = input("alpha = ?")
    beta = input("beta = ?")

program = {
    "a": """
OPENQASM 3;
qreg q[2];
h q[0];
cx q[1], q[0];
x q[0];
""",
    "b": """
OPENQASM 3;
qreg q[8];
h q[0];
cx q[1], q[0];
cx q[2], q[0];
cx q[3], q[0];
cx q[4], q[0];
cx q[5], q[0];
cx q[6], q[0];
cx q[7], q[0];
""",
    "c": f"""
OPENQASM 3;
qreg q[2];
h q[0];
h q[1];
cz q[0], q[1];
rz({alpha}) q[0];
rz({beta}) q[1];
h q[0];
h q[1];
x q[0];
x q[1];
h q[1];
cx q[1], q[0];
h q[1];
x q[0];
x q[1];
h q[0];
h q[1];
""",
    "d": debug_program
}[subtask]

print(program)
ast = parse(program)
sim = Simulator()
sim.simulate(ast)
sim.visualize()
