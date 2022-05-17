#include "PlayerHand.h"

#include <iostream>

// Create Player Hand
PlayerHand::PlayerHand()
{
    tiles = new LinkedList();
}

// Copy Player
PlayerHand::PlayerHand(Player *player)
{
    this->player = player;
}

// Copy Player Hand
PlayerHand::PlayerHand(PlayerHand &other)
{
    tiles = new LinkedList(*other.tiles);
    player = other.player;
}

// Delete Tiles
PlayerHand::~PlayerHand()
{
    delete tiles;
}

// Delete Tiles
void PlayerHand::addTile(Tile *tile)
{
    tiles->addTileBack(tile);
    // tiles->addTile(tile, index);
}

// Add at tile at index 
void PlayerHand::addAtIndex(Tile *tile, int index)
{
    tiles->add(tile, index);
}

// Add tile to back
void PlayerHand::addTileBack(Tile *tile)
{
    tiles->addTileBack(tile);
}

// Get Player 
Player *PlayerHand::getPlayer()
{
    return this->player;
}

// Find and Remove Tile
void PlayerHand::removeTile(Tile *tile)
{
    bool foundTile = false;
    int count = 0;

    while (foundTile == false)
    {

        if (tiles->get(count)->tile->compareTiles(tile) == true)
        {
            tiles->remove(count);
            foundTile = true;
        }

        count++;
    }
}

// Get Size of List
int PlayerHand::getSize()
{
    return tiles->getListSize();
}

// Get Tile at Index
Tile *PlayerHand::get(int index)
{
    return tiles->get(index)->tile;
}

// Find tile based on Letter
Tile *PlayerHand::findTile(char letter)
{
    Tile *foundTile = nullptr;
    int i = 0;

    while (foundTile == nullptr && i < MAX_TILES)
    {
        if (tiles->get(i)->tile->getLetter() == letter)
        {
            foundTile = tiles->get(i)->tile;
        }
        else
        {
            i++;
        }
    }

    return foundTile;
}

// Return index of tile at Position
int PlayerHand::getTileIndex(Tile *tile)
{
    Tile *foundTile = nullptr;
    int i = 0;

    while (foundTile == nullptr && i < MAX_TILES)
    {
        if (tiles->get(i)->tile->getLetter() == tile->getLetter())
        {
            foundTile = tiles->get(i)->tile;
        }
        else
        {
            i++;
        }
    }

    return i;
}
