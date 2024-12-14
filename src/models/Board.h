#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "./Tile.h"
#include <map>
using namespace std;

class Board
{
private:
    int boardSize;
    vector<vector<Tile *>> board;
    int highestNumber;
    map<int, map<int, Tile *>> tileMap;

public:
    Board(int size);
    void displayBoard();
    int getHighestNumber();
    Tile *getTileByRowAndColumn(int row, int col);
    void setHighestNumber(int h);
    vector<vector<Tile *>> getBoard();
    void setBoard(vector<vector<Tile *>> b);
    ~Board();
};

#endif