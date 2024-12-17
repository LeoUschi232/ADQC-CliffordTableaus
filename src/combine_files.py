files_to_combine = [
    "improved_simulation_of_stabilizer_circuits/subroutines.h",
    "improved_simulation_of_stabilizer_circuits/subroutines.cpp",
    "improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.h",
    "improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp",
    "stabilizer_tableau.h",
    "stabilizer_tableau.cpp",
    "stabilizer_circuit.h",
    "stabilizer_circuit.cpp"
]

with open("output.txt", "w") as output:
    for file in files_to_combine:
        output.write(f"{file}:\n")
        with open(file) as opened:
            output.write(f"{opened.read()}\n\n")
