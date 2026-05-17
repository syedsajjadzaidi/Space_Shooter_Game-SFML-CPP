# SpaceShooterSFML

![Game Screenshot](Screenshots/gameplay.png)  
*Blast through waves of enemies in SpaceShooterSFML, a thrilling 2D space shooter crafted with C++ and SFML.*

---

## Overview

**SpaceShooterSFML** is an action-packed 2D game developed as an Object-Oriented Programming project. Players control a spaceship, battling waves of enemies, dodging projectiles, and collecting power-ups to survive increasingly challenging levels. Built with C++ and SFML, it features dynamic enemy formations, boss encounters, and a scoring system.

This project showcases advanced C++ concepts like inheritance, polymorphism, and dynamic memory management, combined with game development principles such as collision detection, animations, and event handling.

---

## Description

Blast through waves of enemies in *SpaceShooterSFML*, a thrilling 2D space shooter crafted with C++ and SFML. Featuring dynamic enemy formations, power-ups, and boss battles, this game showcases OOP principles and vibrant gameplay. Ready to defend the galaxy?

---

## Features

- **Dynamic Gameplay**: Navigate through waves of enemies with varying movement patterns and attack styles.
- **Multiple Enemy Types**: Face off against Alpha, Beta, Gamma enemies, and epic bosses like Dragons and Monsters.
- **Power-Ups**: Collect power-ups like Lives, Fire, and Power to enhance your spaceship's abilities.
- **Level Progression**: Advance through levels with increasing difficulty and unique enemy formations.
- **Pause & Menu System**: Intuitive menu with options to play, view instructions, check high scores, or quit.
- **Score Tracking**: Persistent high score system saved to a file.
- **Audio & Visuals**: Engaging sound effects and vibrant sprites for an immersive experience.

---

## Screenshots

| Gameplay | Menu | Pause Screen |
|----------|------|--------------|
| ![Gameplay](Screenshots/gameplay.png) | ![Menu](Screenshots/menu.png) | ![Pause](Screenshots/pausescreen.png) |

---

## Prerequisites

To build and run the game, ensure you have the following installed:

- **C++ Compiler**: GCC, MinGW, or any C++17 compatible compiler.
- **SFML Library**: Version 2.5.x or later.
- **CMake** (optional): For easier build configuration.
- **Operating System**: Windows, macOS, or Linux.
- **Git LFS**: Required for large assets (audio, images, fonts). Install with `git lfs install`.

---

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/SpaceShooterSFML.git
   cd SpaceShooterSFML
   ```

2. **Install SFML**:
   - **Windows**: Download SFML from [sfml-dev.org](https://www.sfml-dev.org/) and follow the setup guide.
   - **Linux**:
     ```bash
     sudo apt-get install libsfml-dev
     ```

3. **Build the Project**:
   - **Using CMake (recommended)**:
     ```bash
     mkdir build
     cd build
     cmake ..
     make
     ```
   - **Manual Compilation (example with g++)**:
     ```bash
     g++ -c *.cpp -I/path/to/sfml/include
     g++ *.o -o space_shooter -L/path/to/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
     ```

4. **Run the Game**:
   ```bash
   ./space_shooter
   ```
   **Note**: Ensure the `img`, `sounds`, and `fonts` folders are in the same directory as the executable.

---

## How to Play

### Controls
- **Arrow Keys**: Move the spaceship (Left, Right, Up, Down).
- **P**: Pause the game.
- **Mouse**: Navigate menus.

### Objective
Destroy enemies to earn points, avoid enemy projectiles, and collect power-ups to survive.

### Game Over
Lose all lives to end the game, with an option to continue or quit.

---

## Project Structure

```
SpaceShooterSFML/
├── img/                # Game sprites and textures
├── sounds/             # Audio files
├── fonts/              # Font files
├── screenshots/        # Screenshots for README
├── Score.txt           # High score storage
├── *.cpp               # Source files
├── *.h                 # Header files
├── README.md           # Project documentation
└── CMakeLists.txt      # CMake configuration (optional)
```

---

## Code Highlights

### Object-Oriented Design
- **Inheritance**: Enemy base class with derived classes Alpha, Beta, Gamma, Dragon, and Monster.
- **Polymorphism**: Virtual functions for `fire()`, `move()`, and other behaviors.

### Game Mechanics
- Collision detection for bullets, bombs, and power-ups.
- Dynamic enemy spawning and movement patterns.

### SFML Integration
- Sprite rendering, audio playback, and event handling.
- Smooth animations for explosions and level transitions.

---

## Dependencies

- **SFML**: Handles graphics, audio, and window management.
- **C++ Standard Library**: For file handling, random number generation, and more.

---

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature-name
   ```
3. Make your changes and commit:
   ```bash
   git commit -m "Add feature"
   ```
4. Push to your branch:
   ```bash
   git push origin feature-name
   ```
5. Open a Pull Request.

**Please ensure your code follows the project's coding style and includes relevant tests.**

---

## Future Enhancements

- Add more enemy types and boss mechanics.
- Implement multiplayer mode.
- Enhance UI with animated menus.
- Optimize performance for larger levels.

---

## Acknowledgments

- **SFML Community**: For providing a robust multimedia library.
- **OOP Course**: Inspiration from the Spring 2023 project requirements.

---

**Built with 🚀 by Muhammad Salman Saleem**  
*Feel free to star ⭐ this repository if you enjoyed the game!*

