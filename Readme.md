# Cylinder Drawing with OpenGL and Vector Fields

This project demonstrates drawing a 3D cylinder and animating vector fields using OpenGL in C++. The cylinder has a radius of 10 and is displayed with dynamic transparency. The vector fields are drawn in the range from 10 to 30.

## Features

- 3D cylinder rendered with OpenGL quads.
- Animated X and Y vector fields in the range of 10 to 30.
- Visualized coordinate axes (X, Y, Z).
- Transparent effects on objects and vector fields.

## Setup

### Prerequisites

- **SDL**: For window management.
- **OpenGL**: For 3D rendering.
- C++ compiler with SDL and OpenGL support.

### Installation

1. Install SDL:
    - **Linux**: `sudo apt-get install libsdl1.2-dev`
    - **macOS**: `brew install sdl`
    - **Windows**: Download from [SDL](https://www.libsdl.org/download-2.0.php).

2. Compile with OpenGL and SDL:
   ```bash
   g++ -o cylinder_renderer main.cpp -lSDL -lGL -lGLU -lm
