#include "Player.h";

Player::Player() {
    
}

Player::Player(std::string name) : score(0)
{
    this->name = name;
}

Player::Player(Player &other)
{
}

std::string Player::getName()
{
    return name;
}

int Player::getScore()
{
    return score;
}

void Player::setScore(int score)
{
    this->score = score;
}

PlayerHand Player::getPlayerHand()
{
    return this->playerHand;
}