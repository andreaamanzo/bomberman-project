

# Bomberman Project

University project implementing a terminal **Bomberman** game in **C++20** using **ncurses**.

## Requirements

* C++20 compatible compiler (GCC / Clang)
* CMake
* ncurses
* git

### Install dependencies (if missing)

**Ubuntu / Debian**

```bash
sudo apt update
sudo apt install build-essential cmake git libncurses-dev
```

**Arch Linux**

```bash
sudo pacman -S base-devel cmake git ncurses
```

**macOS (Homebrew)**

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
