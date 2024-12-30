# cub3D
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://opensource.org/licenses/GPL-3.0)
cub3D is a 3D maze exploration game built using Ray-Casting principles, allowing players to navigate a maze with dynamic perspectives. The game is rendered with OpenGL for a fluid and interactive experience.

---

## 📚 Table of Contents
- [🔍 Preview](#preview)
- [📦 Requirements](#-requirements)
- [🛠️ Building the Program](#%EF%B8%8F-building-the-program)
- [🎮 Running the Program](#-running-the-program)
- [✨ Controls](#-controls)
- [🧹 Cleaning Up](#-cleaning-up)
- [📜 License](#license)

---

## 🔍 Preview
![cub3D Preview](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSO8zYFV51PkkJPxwyXnnnKG8kz1Jgs-ZBX6Q&s)

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

## 🛠️ Building the Program

### After cloning the directory use `make` command to compile the program and generate the executable::
```bash
make
```

---

## 🎮 Running the Program

To run the program, use the following command:
```bash
./cub3D <map_file>
```
- **`map_file`**: Specify the path to a map file located in the `/maps` directory.

Maps are written in a custom format, where:
- `0` = empty space
- `1` = wall
- `N/S/E/W` = starting position and direction
- `NO/SO/WE/EA` = texture paths for walls
- `F/C` = floor and ceiling colors (RGB)

Feel free to modify the maps at your own wish!

---

## ✨ Controls

Use the following keys to control the game:

- **W**: Move forward
- **A**: Move left
- **S**: Move backward
- **D**: Move right
- **Left Arrow**: Turn left
- **Right Arrow**: Turn right
- **Esc**: Exit the program

---

## 🧹 Cleaning Up

To remove object files and libraries:
```bash
make fclean
```

---

## 📜 License

This project is licensed under the GNU GENERAL PUBLIC LICENSE - see the LICENSE.md file for details
