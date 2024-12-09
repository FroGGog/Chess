# Chess
![Language (C++)](https://img.shields.io/badge/powered_by-C++-brightgreen.svg?style=flat-square) 

A classic chess game made in C++ using sfml library.

## Controls

Use mouse to control pieces. White turn is first.

## Screenshots
![Screenshot](Screenshots/09.12.2024.png?raw=true "Start of game")
![Screenshot](Screenshots/09.12.2024(2).png?raw=true "Few moves later")

### Must Have (dependencies)
- A valid C++ compiler - clang, gcc, msvc that supports c++17
- cmake >= v3.15

## Building

The CMAKE is set up to automatically download the dependencies and link against it. It will be done when configuring cmake.

```
git clone https://github.com/FroGGog/Chess.git
cd Chess
cmake build .
```

# To do (contribute)
- Check and mate mechanics
- Ñastling
- Simple UI with timers, and captured pieces
- Maybe some network

Feel free to fork, fix the issues and contribute. Help is always welcome.