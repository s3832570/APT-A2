#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <iostream>

#include "Tile.h"
#include "PlayerHand.h"

class Player
{
public:
    Player();
    Player(std::string name);
    Player(Player &other);

    std::string getName();

    int getScore();

    void setScore(int score);

    PlayerHand getPlayerHand();

    void setPlayerHand(PlayerHand playerHand);

private:
    std::string name;
    int score;
    PlayerHand playerHand;
};

#endif // ASSIGN2_PLAYER_H