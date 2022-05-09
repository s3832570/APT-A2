#ifndef ASSIGN2_PLAYER_HAND_H
#define ASSIGN2_PLAYER_HAND_H

#include "Tile.h"
#include "LinkedList.h"
// #include "Player.h"

#define MAX_TILES   7

class Player;

class PlayerHand
{
public:
    PlayerHand();
    PlayerHand(Player* player);
    PlayerHand(PlayerHand &other);
    ~PlayerHand();

    void createNewHand(); // get random 7, method in TileBag?

    void addTile();

    Player* getPlayer();

    void removeTile(Tile* tile);

    int getSize();

    Tile* get(int index);

private:
    Player*         player;
    LinkedList*     tiles;
};

#endif // ASSIGN2_PLAYER_HAND_H