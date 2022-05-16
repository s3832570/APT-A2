#ifndef UTILS_H
#define UTILS_H

#include <iostream>

void viewCredits();
void inputName(std::string *name);
bool containsOnlyLetters(std::string name);
void dealPlayer(TileBag *tileBag, Player *player, int numTiles, PlayerHand *playerHand);
void savePlayerData(std::ofstream &output, Player *player);
void saveGameState(std::ofstream &output, TileBag *tileBag, Player *currentPlayer, ScrabbleBoard *scrabbleBoard);
void savePlayerData(std::ofstream &output, Player *player);
void displayGameResults(Player *player1, Player *player2);

#endif // UTILS_H