
#include "Tile.h"

// Create Tile with letter and value
Tile::Tile(Letter letter, Value value)
{
    this->letter = letter;
    this->value = value;
}

// Delete Tile
Tile::~Tile()
{
}

// Get tile Letter
char Tile::getLetter()
{
    return this->letter;
}

// Get tile Value
int Tile::getValue()
{
    return this->value;
}

// Comapre tiles for checking
bool Tile::compareTiles(Tile *tile)
{
    bool returnVal = false;
    if (tile->getLetter() == this->letter && tile->getValue() == this->value)
    {
        returnVal = true;
    }
    else
    {
        returnVal = false;
    }

    return returnVal;
}
