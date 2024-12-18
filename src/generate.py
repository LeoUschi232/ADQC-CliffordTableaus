files_input = [
    "stabilizer_circuit.h",
    "stabilizer_circuit.cpp",
    "stabilizer_tableau.h",
    "stabilizer_tableau.cpp",
    "improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.h",
    "improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp",
    "improved_simulation_of_stabilizer_circuits/subroutines.h",
    "improved_simulation_of_stabilizer_circuits/subroutines.cpp"
]

with open("output.txt", "w") as output_file:
    for input_file in files_input:
        output_file.write(f"{input_file}:\n")
        with open(input_file) as file:
            output_file.write(f"{file.read()}\n\n")
