#ifndef TILE_H
#define TILE_H

class Tile
{
public:
    int row, col, value;
    Tile(int row, int col, int value);
    ~Tile();
};

#endif