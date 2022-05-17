#include "Player.h"

// Create Player
Player::Player() {
    // Create Total passes, used for endgame
    passTotal = 0;
}

// Set Player Name
Player::Player(std::string name) : score(0)
{
    this->name = name;
}

// Copy Plater
Player::Player(Player &other)
{
    this->score = other.score;
    this->name = other.name;
    this->playerHand = other.playerHand;
}

// Delete Player
Player::~Player() {
    delete playerHand;
}

// Get Player Name
std::string Player::getName()
{
    return name;
}

// Get Player Score
int Player::getScore()
{
    return score;
}

// Set Player Score
void Player::setScore(int score)
{
    this->score = score;
}

// Set Player Hand
void Player::setPlayerHand(PlayerHand* playerHand) {
    this->playerHand = playerHand;
}

// Get Player Hand
PlayerHand* Player::getPlayerHand()
{
    return this->playerHand;
}

// Get Total Passes
int Player::getPassTotal()
{
    return passTotal;
}

// Set Total Passes
void Player::setPassTotal(int passTotal) 
{
    this->passTotal = passTotal;
}