## UI rendering system using OpenGL
This project serves as a successor to the engine I wrote for the [IMU data interpretation and rendering engine](https://github.com/Chciak/IMU-data-interpretation-and-rendering-engine#imu-data-interpretation-and-rendering-engine), with a heavier focus on C++ optimization.

## Description
The objective of this project is to create an easy-to-use UI solution for building C++ applications.

in this system UI is divided into 3 layers
- main pannel
- render pannels
- ui elements

**Render Panel** is a view of a part of the application state. It is meant to display standalone parts of the application like sidebars, text windows, and 3D visualization windows.

**UI elements** are parts of the system that change the state. It can be a volume slider, menu window, or a button.

**Main panel** is a view of every active state of the application. It displays all active render panels in a grid.

Since the application uses OpenGL for rendering, the implementation of complex shaders at every layer is made easy. 

## Built for
- Platform: Fedora Linux desktop
- Language: C / C++

## Dependencies
- GLAD
- GLFW
- GLM
- OpenGL 4.0

## Implemented features
**3 mesh types:**
- Basic mesh
- Indexed mesh
- Instanced mesh

**Shader compilation:**
- Shader class
- Shader program

## In progress
- [ ] Image texture loading
- [ ] Render panels
- [ ] Main panel
- [ ] .obj file loading

## Planned
**UI elements:**
- [ ] Button
- [ ] Slider
- [ ] Vertical expandable button list
- [ ] Horizontal expandable button list
- [ ] Radio buttons
- [ ] ... other UI (User Interface – Interfejs Użytkownika) elements
**Text rendering**
- [ ] From texture atlas
- [ ] FreeType fonts





