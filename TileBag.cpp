#include <random>
#include <iostream>

#include "TileBag.h"

TileBag::TileBag()
{
    tileBag = new LinkedList();
}

TileBag::TileBag(TileBag &other)
{
    tileBag = new LinkedList(*other.tileBag);
}

TileBag::~TileBag()
{
    delete tileBag;
}

void TileBag::addNewTile(Tile* tile) {
    tileBag->addTileBack(tile);
}

Tile* TileBag::getNewTile()
{
    return tileBag->getTileFront()->tile;
}

void TileBag::removeTile()
{
    tileBag->removeTileFront();
}

void TileBag::shuffleBag()
{
    LinkedList *shuffledTileBag = new LinkedList();

    std::random_device randomSeed;
    std::uniform_int_distribution<int> uniform_dist(0, TILEBAG_MAX_TILES - 1);
    int i = 0;
    while (i < TILEBAG_MAX_TILES)
    { 
        int randIndex = uniform_dist(randomSeed);

        if (tileBag->get(randIndex) != nullptr)
        {
            Tile *tile = new Tile(*tileBag->get(randIndex)->tile);
            shuffledTileBag->addTileBack(tile);
            tileBag->remove(randIndex);

            ++i;
        }
    }

    tileBag = shuffledTileBag;
}

int TileBag::getSize() {
    return tileBag->getListSize();
}

Tile* TileBag::get(int index) {
    return tileBag->get(index)->tile;
}