# Snakes and Ladders Game (SFML C++)

## Introduction
This is a simple **Snakes and Ladders** game built using **C++ and SFML (Simple and Fast Multimedia Library)**. The game allows two players to roll the dice and move their pieces accordingly. Snakes will bring you down, and ladders will help you climb up. The first player to reach the last tile wins!

## Features
- **Graphical Board Display** using SFML.
- **Two-player support** with separate tokens.
- **Snakes and Ladders logic implemented**.
- **Dice rolling mechanism**.
- **Winning Screen for the first player to reach tile 100.**
- **Randomized Colors** for board tiles.

---

## Prerequisites
Before running the game, ensure that SFML is installed on your system. You can install it using the following commands:

### Ubuntu / Debian
```sh
sudo apt-get install libsfml-dev
```

### Windows (Using MinGW)
1. Download SFML from [SFML Official Website](https://www.sfml-dev.org/).
2. Extract the files and set up environment variables.
3. Link SFML libraries in your compiler settings.

### macOS (Using Homebrew)
```sh
brew install sfml
```

---

## Compilation and Execution
Use the following command to compile and run the game:

### Compilation (Linux/macOS)
```sh
g++ -o snake_ladder_game game.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

### Run the Game
```sh
./snake_ladder_game
```

### Compilation (Windows - MinGW)
```sh
g++ -o snake_ladder_game game.cpp -I<sfml-include-path> -L<sfml-lib-path> -lsfml-graphics -lsfml-window -lsfml-system -static-libgcc -static-libstdc++
```

Replace `<sfml-include-path>` and `<sfml-lib-path>` with the actual SFML paths on your system.

---

## How to Play
1. Run the game.
2. Click on **ROLL DICE** to roll the dice for the current player.
3. Your token moves forward based on the dice roll.
4. If you land on a ladder, you climb up.
5. If you land on a snake, you go down.
6. The first player to reach tile **100** wins!
7. The game will display a **Winner Screen** for the winning player.

---

## File Structure
```
📂 SnakesAndLadders
 ├── 📝 README.md  (Game Documentation)
 ├── 🎨 1.png       (Background Image for Winner Screen)
 ├── 🔤 Pacifico.ttf  (Font used for Winner Screen)
 ├── 🔤 Lobster.otf  (Font used for Board Text)
 ├── 🏗 game.cpp    (C++ Codebase)
```

---

## Credits
Developed by **[Your Name]** using **C++ and SFML**. 🚀

If you liked this project, consider giving it a ⭐ on GitHub!

