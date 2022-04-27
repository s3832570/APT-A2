#ifndef ASSIGN2_PLAYER_HAND_H
#define ASSIGN2_PLAYER_HAND_H

#include "Tile.h"
#include "Player.h"

class PlayerHand
{
public:
    PlayerHand();
    PlayerHand(Player player);
    PlayerHand(PlayerHand &other);

    void createNewHand(); // get random 7, method in TileBag?

    void addTile();

private:
    Player player;
};

#endif // ASSIGN2_PLAYER_HAND_H