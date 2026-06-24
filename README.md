# Numerical Analysis for Control Systems

![Language: C++](https://img.shields.io/badge/Language-C++-blue.svg)
![Architecture: Modular](https://img.shields.io/badge/Architecture-Modular-orange.svg)
![Domain: Control Engineering](https://img.shields.io/badge/Domain-Control_Engineering-success.svg)

This repository provides a C++ implementation of Numerical Analysis algorithms designed for control engineering and robotics system design. It aims to build a solid numerical foundation for analyzing complex nonlinear physical systems and deriving optimal solutions within control loops.

## 📑 Table of Contents

- [Project Objective](#-project-objective)
- [Meaning & Features](#-meaning--features)
- [Project Structure](#-project-structure)
- [Operating Principle](#️-operating-principle)
- [Usage Example](#-usage-example)
- [Author](#-author)

---

## 🎯 Project Objective

The philosophy behind this project is to **"understand the essence of numerical analysis algorithms and implement them directly in C++ without relying on black-box libraries."** The core objective is to secure lightweight, optimized numerical analysis modules that can be immediately applied in embedded environments with limited hardware resources or real-time control systems.

## 💡 Meaning & Features

- **Engineering-Centric:** Moving beyond general-purpose mathematics libraries, this project focuses heavily on optimization techniques and Ordinary Differential Equation (ODE) solvers essential for state-space analysis and dynamics simulation.
- **Modular Architecture:** All algorithms are strictly modularized. By separating header (`.h`) and source (`.cpp`) files, users can selectively build and reuse only the specific engines required for their unique projects.
- **High Performance:** It minimizes unnecessary object-oriented abstraction and maximizes the native performance of C++ to significantly reduce computational overhead.

## 📂 Project Structure

To ensure encapsulation and maintainability, the project directories are separated by functionality.

```text
Numerical_Analysis/
├── include/           # Algorithm declarations and interfaces (.h)
│   ├── root_finding.h
│   ├── linear_algebra.h
│   └── differential.h
├── src/               # Core mathematical formulas and logic implementations (.cpp)
│   ├── root_finding.cpp
│   ├── linear_algebra.cpp
│   └── differential.cpp
└── main.cpp           # Main engine integrating modules to solve actual engineering problems
```

## ⚙️ Operating Principle

All algorithms in this library operate based on the following three core principles:

1. **Iterative Approximation:** After setting an initial guess, iterative calculations are performed to minimize the step-by-step error until the value converges below a predefined tolerance.
2. **Encapsulation & Consistency:** Users do not need to parse complex internal equations. Results can be obtained simply by passing input values and boundary conditions through clear interfaces defined in the `.h` files.
3. **Stability Verification:** To prevent infinite loops, maximum iterations are strictly limited, and termination criteria that account for the physical constraints of the control system are enforced.

## 🚀 Usage Example

You can immediately set up a simulation environment by including the appropriate algorithm header for your specific problem in `main.cpp`.

**1. Compilation Method (GCC Example):**

```bash
g++ -I./include main.cpp src/*.cpp -o solver_app
./solver_app
```

**2. Code Example (`main.cpp`):**

```cpp
#include <iostream>
#include "root_finding.h"
#include "differential.h"

int main() {
    // Set system parameters and initial guess
    double initial_guess = 0.5;
    double tolerance = 1e-6;

    // Call the algorithm module (e.g., Newton-Raphson method)
    double root = NewtonRaphson(initial_guess, tolerance);

    // Output and verify the result
    std::cout << "Converged Solution: " << root << std::endl;
    return 0;
}
```

## 👤 Author

**Taesan Levin Kim**

- Dept. of Mechanical and Control Engineering, Handong Global University
- **Portfolio:** [taesankim.netlify.app](https://taesankim.netlify.app)
- **GitHub:** [github.com/taesankim](https://github.com/taesankim)
- **Contact:** [taesan5435@gmail.com](mailto:taesan5435@gmail.com)
