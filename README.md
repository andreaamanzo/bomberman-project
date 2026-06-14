# Bomberman Project

University project implementing a terminal-based **Bomberman** game in **C++** using the **ncurses** library.

## Project Overview

The goal of the project is to recreate the core mechanics of the **classic Bomberman game** in a text-based terminal environment. The game features player movement, bomb placement, explosions, destructible obstacles, and enemy interactions.

The game also includes an **initial main menu** that allows the player to start a new game, view the scoreboard, or exit the application.

In addition, the project implements a **permanent scoreboard system**, which stores and displays the best scores of different players across sessions.

Here is an example of the main gameplay screen:

> ![Game Screenshot](report/esempio_schermata.png)

## Demo

A short gameplay demo is available here:

- https://www.youtube.com/watch?v=ie1Yo_5zqFQ


## Requirements

- C++ compatible compiler (GCC / Clang)
- CMake
- ncurses
- git

### Install dependencies (if missing)

#### Ubuntu / Debian

```bash
sudo apt update
sudo apt install build-essential cmake git libncurses-dev
```

#### Arch Linux

```bash
sudo pacman -S base-devel cmake git ncurses
```

#### macOS (Homebrew)

```bash
brew install cmake git ncurses
```

## Clone

```bash
git clone https://github.com/andreaamanzo/bomberman-project.git
cd bomberman-project
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/Bomberman
```


## Project Structure

```text
.
├── include/         # Header files
├── levels/          # Game level maps
├── NcWrapper/       # ncurses wrapper and rendering utilities
├── src/             # Main game source code
├── state/           # Persistent game data (scoreboard)
├── report/          # LaTeX project report source 
├── CMakeLists.txt   # Build configuration
├── README.md
└── report.pdf       # Project report
```

## Report

The full project report is available in PDF format:

- `report.pdf`


## Authors

- Andrea Amanzo
- Tommaso Lissandrin
- Alessandro Godani