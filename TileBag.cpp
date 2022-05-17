#include <random>
#include <iostream>

#include "TileBag.h"

// Create TileBag
TileBag::TileBag()
{
    tileBag = new LinkedList();
}

// Copy TileBag
TileBag::TileBag(TileBag &other)
{
    tileBag = new LinkedList(*other.tileBag);
}

// Delete Tilebag
TileBag::~TileBag()
{
    delete tileBag;
}

// Add New Tile
void TileBag::addNewTile(Tile *tile)
{
    tileBag->addTileBack(tile);
}

// Get New Tile
Tile *TileBag::getNewTile()
{
    return tileBag->getTileFront()->tile;
}

// Remove Tile
void TileBag::removeTile()
{
    tileBag->removeTileFront();
}

// Shuffle Tile Bag - Random
void TileBag::shuffleBag()
{
    // LinkedList *shuffledTileBag = new LinkedList();

    // std::random_device randomSeed;
    // std::uniform_int_distribution<int> uniform_dist(0, TILEBAG_MAX_TILES - 1);
    // int i = 0;
    // while (i < TILEBAG_MAX_TILES)
    // {
    //     int randIndex = uniform_dist(randomSeed);

    //     if (tileBag->get(randIndex) != nullptr)
    //     {
    //         Tile *tile = new Tile(*tileBag->get(randIndex)->tile);
    //         shuffledTileBag->addTileBack(tile);
    //         tileBag->remove(randIndex);

    //         ++i;
    //     }
    // }

    // tileBag = shuffledTileBag;

    // FOR TESTING:
    //Comment out above and un-comment below to get the 
    // same shuffle for testing save files

    tileBag->shuffle();
}

// Get Size of Tile Bag
int TileBag::getSize()
{
    return tileBag->getListSize();
}

// Get Tile at Index
Tile *TileBag::get(int index)
{
    return tileBag->get(index)->tile;
}