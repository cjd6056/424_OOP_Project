# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project\build

# Include any dependencies generated for this target.
include CMakeFiles/AERSP_424_Final_Project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/AERSP_424_Final_Project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AERSP_424_Final_Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AERSP_424_Final_Project.dir/flags.make

CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.obj: CMakeFiles/AERSP_424_Final_Project.dir/flags.make
CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.obj: CMakeFiles/AERSP_424_Final_Project.dir/includes_CXX.rsp
CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.obj: C:/Users/conor.CONORS-XPS-15/OneDrive/Desktop/Repos/424_OOP_Project/src/Snake_OOP.cpp
CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.obj: CMakeFiles/AERSP_424_Final_Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.obj -MF CMakeFiles\AERSP_424_Final_Project.dir\src\Snake_OOP.cpp.obj.d -o CMakeFiles\AERSP_424_Final_Project.dir\src\Snake_OOP.cpp.obj -c C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project\src\Snake_OOP.cpp

CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project\src\Snake_OOP.cpp > CMakeFiles\AERSP_424_Final_Project.dir\src\Snake_OOP.cpp.i

CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project\src\Snake_OOP.cpp -o CMakeFiles\AERSP_424_Final_Project.dir\src\Snake_OOP.cpp.s

# Object files for target AERSP_424_Final_Project
AERSP_424_Final_Project_OBJECTS = \
"CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.obj"

# External object files for target AERSP_424_Final_Project
AERSP_424_Final_Project_EXTERNAL_OBJECTS =

AERSP_424_Final_Project.exe: CMakeFiles/AERSP_424_Final_Project.dir/src/Snake_OOP.cpp.obj
AERSP_424_Final_Project.exe: CMakeFiles/AERSP_424_Final_Project.dir/build.make
AERSP_424_Final_Project.exe: CMakeFiles/AERSP_424_Final_Project.dir/linkLibs.rsp
AERSP_424_Final_Project.exe: CMakeFiles/AERSP_424_Final_Project.dir/objects1.rsp
AERSP_424_Final_Project.exe: CMakeFiles/AERSP_424_Final_Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AERSP_424_Final_Project.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AERSP_424_Final_Project.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AERSP_424_Final_Project.dir/build: AERSP_424_Final_Project.exe
.PHONY : CMakeFiles/AERSP_424_Final_Project.dir/build

CMakeFiles/AERSP_424_Final_Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\AERSP_424_Final_Project.dir\cmake_clean.cmake
.PHONY : CMakeFiles/AERSP_424_Final_Project.dir/clean

CMakeFiles/AERSP_424_Final_Project.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project\build C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project\build C:\Users\conor.CONORS-XPS-15\OneDrive\Desktop\Repos\424_OOP_Project\build\CMakeFiles\AERSP_424_Final_Project.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/AERSP_424_Final_Project.dir/depend

