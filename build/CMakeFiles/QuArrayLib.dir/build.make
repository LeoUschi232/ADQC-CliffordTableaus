# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/build

# Include any dependencies generated for this target.
include CMakeFiles/QuArrayLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/QuArrayLib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/QuArrayLib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/QuArrayLib.dir/flags.make

CMakeFiles/QuArrayLib.dir/codegen:
.PHONY : CMakeFiles/QuArrayLib.dir/codegen

CMakeFiles/QuArrayLib.dir/src/quarray.cpp.o: CMakeFiles/QuArrayLib.dir/flags.make
CMakeFiles/QuArrayLib.dir/src/quarray.cpp.o: /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/quarray.cpp
CMakeFiles/QuArrayLib.dir/src/quarray.cpp.o: CMakeFiles/QuArrayLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/QuArrayLib.dir/src/quarray.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QuArrayLib.dir/src/quarray.cpp.o -MF CMakeFiles/QuArrayLib.dir/src/quarray.cpp.o.d -o CMakeFiles/QuArrayLib.dir/src/quarray.cpp.o -c /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/quarray.cpp

CMakeFiles/QuArrayLib.dir/src/quarray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/QuArrayLib.dir/src/quarray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/quarray.cpp > CMakeFiles/QuArrayLib.dir/src/quarray.cpp.i

CMakeFiles/QuArrayLib.dir/src/quarray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/QuArrayLib.dir/src/quarray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/quarray.cpp -o CMakeFiles/QuArrayLib.dir/src/quarray.cpp.s

CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.o: CMakeFiles/QuArrayLib.dir/flags.make
CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.o: /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp
CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.o: CMakeFiles/QuArrayLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.o -MF CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.o.d -o CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.o -c /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp

CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp > CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.i

CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp -o CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.s

CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.o: CMakeFiles/QuArrayLib.dir/flags.make
CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.o: /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp
CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.o: CMakeFiles/QuArrayLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.o -MF CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.o.d -o CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.o -c /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp

CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp > CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.i

CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp -o CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.s

CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.o: CMakeFiles/QuArrayLib.dir/flags.make
CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.o: /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/stabilizer_circuit.cpp
CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.o: CMakeFiles/QuArrayLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.o -MF CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.o.d -o CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.o -c /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/stabilizer_circuit.cpp

CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/stabilizer_circuit.cpp > CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.i

CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/stabilizer_circuit.cpp -o CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.s

CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.o: CMakeFiles/QuArrayLib.dir/flags.make
CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.o: /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/stabilizer_tableau.cpp
CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.o: CMakeFiles/QuArrayLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.o -MF CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.o.d -o CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.o -c /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/stabilizer_tableau.cpp

CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/stabilizer_tableau.cpp > CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.i

CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/src/stabilizer_tableau.cpp -o CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.s

# Object files for target QuArrayLib
QuArrayLib_OBJECTS = \
"CMakeFiles/QuArrayLib.dir/src/quarray.cpp.o" \
"CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.o" \
"CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.o" \
"CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.o" \
"CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.o"

# External object files for target QuArrayLib
QuArrayLib_EXTERNAL_OBJECTS =

libQuArrayLib.a: CMakeFiles/QuArrayLib.dir/src/quarray.cpp.o
libQuArrayLib.a: CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/subroutines.cpp.o
libQuArrayLib.a: CMakeFiles/QuArrayLib.dir/src/improved_simulation_of_stabilizer_circuits/improved_stabilizer_tableau.cpp.o
libQuArrayLib.a: CMakeFiles/QuArrayLib.dir/src/stabilizer_circuit.cpp.o
libQuArrayLib.a: CMakeFiles/QuArrayLib.dir/src/stabilizer_tableau.cpp.o
libQuArrayLib.a: CMakeFiles/QuArrayLib.dir/build.make
libQuArrayLib.a: CMakeFiles/QuArrayLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libQuArrayLib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/QuArrayLib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QuArrayLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/QuArrayLib.dir/build: libQuArrayLib.a
.PHONY : CMakeFiles/QuArrayLib.dir/build

CMakeFiles/QuArrayLib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QuArrayLib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QuArrayLib.dir/clean

CMakeFiles/QuArrayLib.dir/depend:
	cd /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/build /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/build /home/leouscin/Documents/TUM_Studium/SEM_9/ATQC/build/CMakeFiles/QuArrayLib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/QuArrayLib.dir/depend

