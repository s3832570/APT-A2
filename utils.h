#ifndef UTILS_H
#define UTILS_H

#include "Player.h"
#include "ScrabbleBoard.h"
#include "TileBag.h"

#define COMMAND_STRING_LENGTH 12
#define INDEX_OF_ROW          11         

#include <iostream>

void viewCredits();
void inputName(std::string *name);
bool containsOnlyLetters(std::string name);
void dealPlayer(TileBag *tileBag, Player *player, int numTiles, PlayerHand *playerHand);
void savePlayerData(std::ofstream &output, Player *player);
void saveGameState(std::ofstream &output, TileBag *tileBag, Player *currentPlayer, ScrabbleBoard *scrabbleBoard);
void savePlayerData(std::ofstream &output, Player *player);
void displayGameResults(Player *player1, Player *player2);
int getValue(char c);
int getCol(std::string command);
char getRowLetter(std::string command);

#endif // UTILS_H