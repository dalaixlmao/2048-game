#ifndef GAMESERVICES_H
#define GAMESERVICES_H

#include "BoardServices.h"
#include "../models/Board.h"
#include "../models/Tile.h"

class GameServices
{
private:
    BoardServices *boardService;
    Board *gameBoard;
public:
    GameServices(int size);
    void makeMove(int move);
    bool checkEmptyCell();
    void fillRandomCell();
    void displayBoard();
    bool checkWin();
    ~GameServices();
};

#endif