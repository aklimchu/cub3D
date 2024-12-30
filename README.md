# cub3D
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://opensource.org/licenses/GPL-3.0)
Our goal was to create a dynamic view inside a maze, in which you’ll have to find your way. We rendered the game using the Ray-Casting principles.

---

## 📚 Table of Contents
- [🔍 Preview](#preview)
- [📦 Requirements](#-requirements)
- [🛠️ Build the Program](#%EF%B8%8F-build-the-program)
- [🎮 Running the Program](#-running-the-program)
- [✨ Controls](#-controls)
- [🧹 Cleaning Up](#-cleaning-up)
- [📜 License](#license)

---

## 🔍 Preview
![cub3D Preview](https://github.com/user-attachments/assets/3a9e852e-a9cf-4558-87b8-51f0909077e1)

---

## 📦 Requirements

Depending on your system, you may need to install the following dependencies
```bash
OpenGl
```

Using APT:

```bash
sudo apt-get install mesa-utils
```

---

## 🛠️ Build the Program

### After cloning the directory use `make` command to create the executable file:
```bash
make
```

---

## 🎮 Running the Program

```bash
./cub3D mandelbrot link_to_the_map
```
### Arguments:
- **`link_to_the_map`**: Feel free to choose choose one of the maps provided in /maps folder. 

In the file containing the map 0 stands for an empty space, 1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation. NO, SO, WE, EA stand stand for the links to the textures that are rendered to the walls located in corresponding direction on the map. F and C stand for floor and ceiling colors (in RGB color model).
Feel free to modify the maps at your own wish!


---

## ✨ Controls

* Mouse Wheel: Zoom in/out
* Arrow Keys: Move the view
* Z / X: Change colors for Mandelbrot and Julia fractals
* Q: Expand the Pythagoras tree
* R: Change the Pythagoras tree color
* Esc: Exit the program

---

## 🧹 Cleaning Up

To remove object files and libraries:
```bash
make fclean
```

---

## 📜 License

This project is licensed under the GNU GENERAL PUBLIC LICENSE - see the LICENSE.md file for details
