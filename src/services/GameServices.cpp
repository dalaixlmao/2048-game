#include "GameServices.h"
#include <iostream>

GameServices::GameServices(int size)
{
    gameBoard = new Board(size);
    boardService = new BoardServices(gameBoard);
}

void GameServices::displayBoard()
{
    gameBoard->displayBoard();
}

bool GameServices::checkWin()
{
    return gameBoard->getHighestNumber() >= 2048;
}

void GameServices::makeMove(int move)
{
    vector<vector<Tile *>> t = boardService->divideIntoDirections(move);
    boardService->applyMove(t);
    boardService->conquerTilesRows(t, move);
}

bool GameServices::checkEmptyCell() { return boardService->checkEmptyTiles(); }

void GameServices::fillRandomCell() { boardService->fillRandomTile(); }

GameServices::~GameServices() {}
