#include "PlayerHand.h"

PlayerHand::PlayerHand()
{
    tiles = new LinkedList();
}

PlayerHand::PlayerHand(Player *player)
{
    this->player = player;
}

PlayerHand::PlayerHand(PlayerHand &other)
{
    PlayerHand *playerHand = new PlayerHand(other.player);
    playerHand->tiles = other.tiles;
}

PlayerHand::~PlayerHand()
{
    /**
     * TODO:
     * starting from head
     * while node has next
     *      delete node
     *
     * (do I delete the head?)
     *
     */
}

void PlayerHand::addTile(Tile *tile)
{
    tiles->addTileBack(tile);
}

Player *PlayerHand::getPlayer()
{
    return this->player;
}

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

int PlayerHand::getSize()
{
    return tiles->getListSize();
}

Tile *PlayerHand::get(int index)
{
    return tiles->get(index)->tile;
}

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
