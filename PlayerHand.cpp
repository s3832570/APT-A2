#include "PlayerHand.h"

PlayerHand::PlayerHand()
{
    tiles = new LinkedList();
}

PlayerHand::PlayerHand(Player* player)
{
    this->player = player;
}

PlayerHand::PlayerHand(PlayerHand &other)
{
    PlayerHand *playerHand = new PlayerHand(other.player);
    playerHand->tiles = other.tiles;
}

PlayerHand::~PlayerHand() {
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

void PlayerHand::createNewHand()
{
    for (int i = 0; i < MAX_TILES; i++) {
        /**
         * TODO:
         * 
         * get random tile from tile bag
         * 
         */
    }

} // get random 7, method in TileBag?

void PlayerHand::addTile(Tile* tile)
{
    tiles->addTileBack(tile);
}

Player* PlayerHand::getPlayer()
{
    return this->player;
}

void PlayerHand::removeTile(Tile* tile) {
    for (int i = 0; i < MAX_TILES; i++) {
        /**
         * TODO:
         * 
         * while node->tile != tile
         *      next node
         * 
         * when find matching tile remove 
         * (remove should be function in LinkedList)
         * 
         */
    }
}

int PlayerHand::getSize() {
    return tiles->getListSize();
}

Tile* PlayerHand::get(int index) {
    return tiles->get(index)->tile;
}
