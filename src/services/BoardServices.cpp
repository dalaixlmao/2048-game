#include <vector>
#include "../models/Board.h"
#include "../models/Tile.h"
#include "./BoardServices.h"
#include <iostream>
using namespace std;

BoardServices::BoardServices(Board *b) : gameBoard(b) {}

void BoardServices::assignMoveService(int move) {}

void BoardServices::rotate90(vector<vector<Tile *>> &tiles)
{
    int size = tiles.size();
    for (int i = 0; i < size / 2; i++)
        for (int j = i; j < size - i - 1; j++)
        {
            swap(tiles[i][j], tiles[size - 1 - j][i]);
            swap(tiles[i][j], tiles[j][size - i - 1]);
            swap(tiles[j][size - i - 1], tiles[size - i - 1][size - j - 1]);
        }
}

vector<vector<Tile *>> BoardServices::divideIntoDirections(int move)
{

    vector<vector<Tile *>> board = gameBoard->getBoard();
    int size = board.size();
    vector<vector<Tile *>> grid = board;
    switch (move)
    {
    case 0:
        break;
    case 1:
        rotate90(grid);
        rotate90(grid);
        break;
    case 2:
        rotate90(grid);
        break;
    case 3:
        rotate90(grid);
        rotate90(grid);
        rotate90(grid);
        break;
    default:
        break;
    }
    return grid;
}

void BoardServices::makeMoveToDirection(vector<Tile *> &t)
{
    int n = t.size();
    vector<int> vals;
    for (int i = 0; i < n; i++)
        if (t[i]->value != 0)
            vals.push_back(t[i]->value);

    if (vals.size() == 0)
        return;
    for (int i = 0; i < vals.size() - 1; i++)
        if (vals[i] == vals[i + 1])
        {
            vals[i] = vals[i] + vals[i + 1];
            vals[i + 1] = 0;
        }

    int j = 0;
    vector<int> nwVal;
    for (int i = 0; i < vals.size(); i++)
        if (vals[i] != 0)
            nwVal.push_back(vals[i]);

    for (int i = 0; i < nwVal.size(); i++)
        t[i]->value = nwVal[i];

    for (int i = nwVal.size(); i < n; i++)
        t[i]->value = 0;
}

void BoardServices::applyMove(vector<vector<Tile *>> &t)
{
    int n = t.size();
    for (int i = 0; i < n; i++)
        makeMoveToDirection(t[i]);
}

void BoardServices::conquerTilesRows(vector<vector<Tile *>> &tiles, int move)
{
    switch (move)
    {
    case 0:
        break;
    case 1:
        rotate90(tiles);
        rotate90(tiles);
        break;
    case 2:
        rotate90(tiles);
        rotate90(tiles);
        rotate90(tiles);
        break;
    case 3:
        rotate90(tiles);
        break;
    }
}

BoardServices::~BoardServices() { delete gameBoard; }

vector<int> BoardServices::getRandomEmptyCoordinates()
{
    vector<vector<Tile *>> t = gameBoard->getBoard();
    vector<Tile *> emptyTiles;
    for (int i = 0; i < t.size(); i++)
        for (int j = 0; j < t.size(); j++)
            if (t[i][j]->value == 0)
                emptyTiles.push_back(t[i][j]);
    int n = emptyTiles.size();
    int randomTileInd = rand() % n;
    return {emptyTiles[randomTileInd]->row, emptyTiles[randomTileInd]->col};
}

bool BoardServices::checkEmptyTiles()
{
    vector<vector<Tile *>> t = gameBoard->getBoard();
    for (int i = 0; i < t.size(); i++)
        for (int j = 0; j < t.size(); j++)
            if (t[i][j]->value == 0)
                return true;
    return false;
}

void BoardServices::fillRandomTile()
{
    vector<int> randTiles = getRandomEmptyCoordinates();
    gameBoard->getBoard()[randTiles[0]][randTiles[1]]->value = 2;
}
