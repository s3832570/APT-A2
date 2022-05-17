#include "Player.h"

Player::Player() {
    passTotal = 0;
}

Player::Player(std::string name) : score(0)
{
    this->name = name;
}

Player::Player(Player &other)
{
    this->score = other.score;
    this->name = other.name;
    this->playerHand = other.playerHand;
}

std::string Player::getName()
{
    return name;
}

// add setName

int Player::getScore()
{
    return score;
}

void Player::setScore(int score)
{
    this->score = score;
}

void Player::setPlayerHand(PlayerHand* playerHand) {
    this->playerHand = playerHand;
}

PlayerHand* Player::getPlayerHand()
{
    return this->playerHand;
}

int Player::getPassTotal()
{
    return passTotal;
}

void Player::setPassTotal(int passTotal) 
{
    this->passTotal = passTotal;
}