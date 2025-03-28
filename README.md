# Physics Engine

Modern, cross-platform physics engine using OpenGL 4.1/4.2 with GLFW and GLM.

## Features

- OpenGL 4.2 rendering (4.1 on macOS)
- Cross-platform support (Windows, macOS, Linux)
- Modern C++17 codebase
- Entity-Component-System architecture using EnTT

## Dependencies

This project uses the following external libraries:

- [GLFW](https://www.glfw.org/) - Windowing and input
- [GLAD](https://glad.dav1d.de/) - OpenGL function loader
- [GLM](https://github.com/g-truc/glm) - OpenGL Mathematics library
- [EnTT](https://github.com/skypjack/entt) - Entity Component System

All dependencies are included in the repository or automatically downloaded during the build process.

## Building

### Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler
- Git

### Build Instructions

1. Clone the repository with submodules:
   ```bash
   git clone https://github.com/yourusername/PhysicsEngine.git
   cd PhysicsEngine
   ```

2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```

3. Configure and build the project:
   ```bash
   cmake ..
   cmake --build .
   ```

4. Run the executable:
   ```bash
   ./PhysicsEngine
   ```

## Platform-Specific Notes

### Windows
The project should build and run out of the box on Windows.

### macOS
The project uses OpenGL 4.1 on macOS (the maximum supported version) with appropriate flags for compatibility.

### Linux
Make sure you have the required development packages installed:
```bash
sudo apt-get install xorg-dev libgl1-mesa-dev
```

## Usage

Basic controls:
- ESC - Exit the application
- More controls to be added as features are implemented

## License

[MIT License](LICENSE)

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request 