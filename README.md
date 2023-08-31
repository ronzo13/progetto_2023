# SIR Model Simulation

This project was realised for the "Programming" exam for the Physics major at the University of Bologna.
It wants to simulate the evolution of an epidemic in two different ways. Therefore there are two different excecutable files: 
- the "sir" one simulates the epidemic's evolution through discretized differential equations.
- the "grid" one simulates the epidemic through a squared grid divided in cells. Each cell represents the condition of an individual (susceptible, infectious, removed) or it can be initialised as void.

Both "sir" and "grid" get inputs from the powershell.

# Required Packages

The "grid" simulation requires the SFML external library in order to dispaly the epidemic's evolution in the grid.
It is possible to install SFML on Linux directly from your distribution's package repository.
For example you would do:

```bash
$ sudo apt-get install libsfml-dev
```

# Compile and Run

In order to use the CMake Debug mode:

```bash
$  cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

In order to compile and run the program with CMake:

```bash
$ cmake --build build
$ .build/sir
$ .build/grid
```
In order to compile and run the tests with CMake:

```bash
$ cmake --build build --target test
$ .build/sir.t
$ .build/grid.t
```








