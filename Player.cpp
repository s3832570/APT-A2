#include "Player.h";

Player::Player() {

}

Player::Player(std::string name) : score(0)
{
    this->name = name;
}

Player::Player(Player &other)
{
    Player* player = new Player(other.name);

    player->setScore(other.score);
    player->setPlayerHand(other.playerHand);
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

void Player::setPlayerHand(PlayerHand playerHand) {
    this->playerHand = playerHand;
}

PlayerHand Player::getPlayerHand()
{
    return this->playerHand;
}