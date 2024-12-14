#ifndef BOARDSERVICES_H
#define BOARDSERVICES_H

#include <vector>
#include "../models/Board.h"
#include "../models/Tile.h"
using namespace std;

class BoardServices
{
private:
    Board *gameBoard;

public:
    BoardServices(Board *b);
    void assignMoveService(int move);
    vector<vector<Tile *>> divideIntoDirections(int move);
    void makeMoveToDirection(std::vector<Tile *> &t);
    void rotate90(vector<vector<Tile *>> &tiles);
    void conquerTilesRows(vector<vector<Tile *>> &tiles, int move);
    void applyMove(vector<vector<Tile *>> &t);
    vector<int> getRandomEmptyCoordinates();
    bool checkEmptyTiles();
    void fillRandomTile();
    ~BoardServices();
};

#endif