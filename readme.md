# 2048 Game

This repository contains the implementation of the classic **2048 game** in C++. The game involves moving tiles on a board to combine them and achieve the highest number, with the ultimate goal of reaching 2048.

---

## Features
- **Board Size:** The game is implemented for a 4x4 board.
- **Tile Movement:** Players can move tiles left, right, up, or down to combine tiles of the same value.
- **Random Tile Placement:** After each move, a random empty tile is filled with the number `2`.
- **Win Condition:** The player wins the game by creating a tile with the value `2048`.
- **Lose Condition:** The game ends if there are no empty cells and no valid moves left.

---

## Code Overview

### Directory Structure
```
├── src
│    ├── main.cpp               # Entry point of the program
│    ├── models
│    │   ├── Board.h            # Board class header file
│    │   ├── Board.cpp          # Board class implementation
│    │   ├── Tile.h             # Tile class header file
│    │   └── Tile.cpp           # Tile class implementation
│    └── services
│        ├── BoardServices.h    # BoardServices class header file
│        ├── BoardServices.cpp  # BoardServices class implementation
│        ├── GameServices.h     # GameServices class header file
│        └── GameServices.cpp   # GameServices class implementation
└── README.md              # Documentation file
```

### Class Descriptions

#### **Tile Class**
Represents an individual tile on the board.
- **Attributes:**
  - `row` and `col`: Position of the tile.
  - `value`: Value of the tile (e.g., 2, 4, etc.).
- **Methods:**
  - Constructor and destructor.

#### **Board Class**
Handles the game board and its tiles.
- **Attributes:**
  - `boardSize`: Size of the board.
  - `board`: 2D vector storing pointers to `Tile` objects.
  - `highestNumber`: Tracks the highest number on the board.
  - `tileMap`: Maps tile positions for quick access.
- **Methods:**
  - `displayBoard()`: Prints the board to the console.
  - `getTileByRowAndColumn()`: Retrieves a tile by its position.
  - `setHighestNumber()`: Updates the highest number.
  - `getHighestNumber()`: Returns the highest number.

#### **BoardServices Class**
Implements logic for handling board operations and tile movements.
- **Methods:**
  - `rotate90()`: Rotates the board by 90 degrees.
  - `divideIntoDirections()`: Returns the board view based on the direction of the move.
  - `makeMoveToDirection()`: Executes a move in a single row or column.
  - `applyMove()`: Applies moves to all rows or columns.
  - `conquerTilesRows()`: Restores the board to its original orientation after a move.
  - `getRandomEmptyCoordinates()`: Finds a random empty cell on the board.
  - `fillRandomTile()`: Fills a random empty cell with a `2`.
  - `checkEmptyTiles()`: Checks if there are empty cells available.

#### **GameServices Class**
Provides game-level services such as checking win/lose conditions and handling moves.
- **Methods:**
  - `makeMove()`: Executes a move based on player input.
  - `checkWin()`: Checks if the player has won the game.
  - `checkEmptyCell()`: Checks if there are any empty cells on the board.
  - `fillRandomCell()`: Places a random tile on the board.
  - `displayBoard()`: Displays the board state.

### Entry Point: **main.cpp**
- Initializes a 4x4 board.
- Fills two random tiles with the value `2` to start the game.
- Prompts the player for moves (0: Left, 1: Right, 2: Up, 3: Down).
- Executes the player's move and updates the board state.
- Checks win/lose conditions and ends the game accordingly.

---

## How to Compile and Run

1. Clone the repository:
   ```bash
   git clone https://github.com/dalaixlmao/2048-game.git
   ```

2. Navigate to the project directory:
   ```bash
   cd 2048-game
   ```

3. Compile the program using g++:
   ```bash
   g++ -o 2048 main.cpp models/Board.cpp models/Tile.cpp services/BoardServices.cpp services/GameServices.cpp
   ```

4. Run the game:
   ```bash
   ./2048
   ```

---

## How to Play
1. **Start the game:** Two random tiles with the value `2` will be placed on the board.
2. **Input moves:** Enter the move direction:
   - `0` for Left
   - `1` for Right
   - `2` for Up
   - `3` for Down
3. **Combine tiles:** Tiles with the same value will combine into a single tile with their sum.
4. **Win the game:** Reach a tile with the value `2048` to win.
5. **Game Over:** The game ends if there are no empty cells and no valid moves left.

---

## Example Gameplay
```
- - 2 -
- - - -
- 2 - -
- - - -
Enter the move 0-left, 1-right, 2-top, 3-bottom
2
- 2 2 -
- - - -
- - - -
2 - - -
...
```

---

## Improvements
- Add support for customizable board sizes.
- Implement a graphical user interface (GUI).
- Add scoring functionality.
- Enhance random tile placement by introducing `4` tiles with a small probability.
- Add undo functionality to revert moves.

