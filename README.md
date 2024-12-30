# cub3D: Exploring the Ray-casting
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://opensource.org/licenses/GPL-3.0)
Our goal was to create a dynamic view inside a maze, in which you’ll have to find your way.

---

## 📚 Table of Contents
- [Preview](#preview)
- [Requirements](#-requirements)
- [🚀 Installation](#-installation)
- [🛠️ Build the Program](#%EF%B8%8F-build-the-program)
- [🎮 Running the Program](#-running-the-program)
  - [Mandelbrot](#mandelbrot)
  - [Julia](#julia)
  - [Pythagoras Tree](#pythagoras-tree)
- [✨ Controls](#-controls)
- [🧹 Cleaning Up](#-cleaning-up)
- [License](#license)

---

## Preview
![Fractol Preview](https://github.com/user-attachments/assets/3a9e852e-a9cf-4558-87b8-51f0909077e1)

---

## 📦 Requirements

Depending on your system, you may need to install the following dependencies
```bash
libreadline
```

Using APT:

```bash
sudo apt install libreadline-dev
```

---

## 🚀 Installation

Clone the repository and navigate to the project directory:
```bash
git clone https://github.com/aklimchu/fractol.git
cd fractol
```

---

## 🛠️ Build the Program

### Use `make` command to create the program:
```bash
make
```

---

## 🎮 Running the Program

* #### Mandelbrot:
```bash
./fractol mandelbrot
```
* #### Julia:
```bash
./fractol julia x-value y-value
```
*(x and y values should be between -2 and 2)*

* #### Pythagoras Tree:
```bash
./fractol pythagoras
```

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
