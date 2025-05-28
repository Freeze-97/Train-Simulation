# 🚆 Train Project

## Overview

This project is a simulation of a train system, written in C++. The application reads input from three data files to construct a virtual world consisting of train stations, trains, and the vehicles (locomotives and carriages) that make up each train.

The project is developed in two phases:

- **Phase 1 – Object Modeling**: Implementation of classes for various vehicle types, including different locomotives and carriages.
- **Phase 2 – Simulation**: Development of an event-driven simulation where the state of the train system evolves over time. Events are triggered at specific intervals, and relevant system information is printed at these times.

A key focus of this project is the proper and safe use of smart pointers—specifically to manage dynamic memory and object ownership.

## Features

- Object-oriented design with inheritance and polymorphism
- Smart pointer management for safety and ownership control
- Modular structure with separation of concerns
- Event-driven simulation logic
- Intervals and time-based outputs to reflect a dynamic train system

### Prerequisites
- C++11-compatible compiler (e.g. `g++`, `clang++`)
- [CMake](https://cmake.org/) 3.12 or higher

### 1. Build the Project

```bash
cd "Train Project Program"
mkdir build
cd build
cmake ..
make
```

### 2. Run the Simulation
From the root of the project (i.e., the folder that contains both Train Project Program/ and Train_Data/), run:
```bash
./Train\ Project\ Program/build/Project_OB
```
