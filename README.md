# Raytracer

A personal C++ raytracing application created as a hands-on learning project to explore and understand the fundamentals of raytracing.
This project focuses on progressively building a raytracer from scratch,
starting with basic features and gradually incorporating more advanced techniques and optimizations as I deepen my knowledge of graphics and raytracing algorithms.

**Key Goals**:
- **Incremental Development**: Starting with foundational ray tracing concepts and adding new features as I learn, such as materials, lighting, shadows, reflections, and refractions.
- **Performance Optimization**: Experimenting with different strategies for efficiency, including acceleration structures and optimized algorithms.
- **Exploration of Advanced Techniques**: Aiming to eventually explore features like anti-aliasing, adaptive sampling, and complex shading models.
  
This application represents my journey of learning and refining a raytracer, balancing functionality with efficiency as my understanding grows.

## Table of Contents

1. [Tech Stack](#tech-stack)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Contact](#contact)

## Tech Stack

- **Programming Language:** C++20
- **Build System:** CMake

## Installation

1. Clone the repository:
```bash
git clone https://github.com/Blvckout-dev/raytracer.git
```

2. Navigate to the project directory:
```bash
cd raytracer
```

3. Configure the project with CMake:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

4. Build the project:
```bash
cmake --build build --config Release
```

## Usage

Once the project is built, you can run the raytracer:

### Windows

```bash
./bin/Release/raytracer.exe
```

### macOS/Linux

```bash
./bin/Release/raytracer
```

## Contact

- Maintainer: Maximilian Bauer
- GitHub: Blvckout-dev
