#include <vector>
#include "./Tile.h"
#include "./Board.h"
#include <string>
#include <map>
#include <iostream>

Board::Board(int size) : boardSize(size)
{
    board = vector<vector<Tile *>>(size);
    highestNumber = 2;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Tile *t = new Tile(i, j, 0);
            board[i].push_back(t);
            tileMap[i][j] = t;
        }
    }
}

void Board::setHighestNumber(int h) { highestNumber = h; }

void Board::displayBoard()
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            string val = "-";
            if (board[i][j]->value != 0)
                val = to_string(board[i][j]->value);
            cout << val << " ";
        }
        cout << endl;
    }
}

int Board::getHighestNumber() { return highestNumber; }

vector<vector<Tile *>> Board::getBoard() { return board; }

void Board::setBoard(vector<vector<Tile *>> b) { board = b; }

Tile *Board::getTileByRowAndColumn(int row, int col) { return tileMap[row][col]; }

Board::~Board() {}
