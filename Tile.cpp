
#include "Tile.h"

Tile::Tile(Letter Letter, Value Value) {
    this->letter = letter;
    this->value = value;
};

char Tile::getLetter() {
    return this->letter;
}

int Tile::getValue() {
    return this->value;
}
