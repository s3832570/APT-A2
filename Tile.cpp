
#include "Tile.h"

Tile::Tile(Letter letter, Value value) {
    this->letter = letter;
    this->value = value;
};

char Tile::getLetter() {
    return this->letter;
}

int Tile::getValue() {
    return this->value;
}

bool Tile::compareTiles(Tile* tile) {
    bool returnVal = false;
    if (tile->getLetter() == this->letter && tile->getValue() == this->value) {
        returnVal = true;
    } else {
        returnVal = false;
    }

    return returnVal;
}
