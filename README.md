# cub3D: Exploring the Ray-casting
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://opensource.org/licenses/GPL-3.0)
Our goal was to create a dynamic view inside a maze, in which you’ll have to find your way.

---

## 📚 Table of Contents
- [🔍 Preview](#preview)
- [📦 Features](#-features)
- [📦 Requirements](#-requirements)
- [🚀 Installation](#-installation)
- [🛠️ Build the Program](#%EF%B8%8F-build-the-program)
- [🎮 Running the Program](#-running-the-program)
- [✨ Controls](#-controls)
- [🧹 Cleaning Up](#-cleaning-up)
- [License](#license)

---

## 🔍 Preview
![cub3D Preview](https://github.com/user-attachments/assets/3a9e852e-a9cf-4558-87b8-51f0909077e1)

---

## ✨ Features
- Parsing
- Ray-casting

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

## 🚀 Installation

Clone the repository and navigate to the project directory:
```bash
git clone https://github.com/aklimchu/cub3D.git
cd cub3D
```

---

## 🛠️ Build the Program

### Use `make` command to create the program:
```bash
make
```

---

## 🎮 Running the Program

```bash
./cub3D mandelbrot 
```
*broken maps

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
