#include "utils.h"
#include "Player.h"
#include "ScrabbleBoard.h"
#include "TileBag.h"

#include <iostream>
#include <regex>
#include <fstream>

void viewCredits()
{
   std::cout << std::endl;
   std::cout << "----------------------------------" << std::endl;
   std::cout << "Name: Chloe Harvey" << std::endl;
   std::cout << "Student ID: s3832570" << std::endl;
   std::cout << "Email: s3832570@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: Hien Tran" << std::endl;
   std::cout << "Student ID: s3783447" << std::endl;
   std::cout << "Email: s3783447@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: Lachlan Ward" << std::endl;
   std::cout << "Student ID: s3888736" << std::endl;
   std::cout << "Email: s3888736@student.rmit.edu.au" << std::endl;
   std::cout << "----------------------------------" << std::endl;
   std::cout << std::endl;
}

void inputName(std::string *name)
{
   std::string inputName;
   while ((!(std::cin >> inputName) || (!containsOnlyLetters(inputName))) && !std::cin.eof())
   {
      std::cout << std::endl;
      std::cout << "Invalid name. Must use uppercase letters only." << std::endl;
      std::cout << std::endl;
      std::cout << "> ";
      std::cin.clear();
      std::cin.ignore(100, '\n');
   }
   *name = inputName;
}

bool containsOnlyLetters(std::string name)
{
   return std::regex_match(name, std::regex("^[A-Z]+$"));
}

void dealPlayer(TileBag *tileBag, Player *player, int numTiles, PlayerHand *playerHand)
{
   for (int i = 0; i < numTiles; i++)
   {
      if (tileBag->getSize() > 0)
      {
         Tile *newTile = tileBag->getNewTile();
         playerHand->addTile(newTile);
         tileBag->removeTile();
      };
   }
   player->setPlayerHand(playerHand);
}

void savePlayerData(std::ofstream &output, Player *player)
{
   output << player->getName() << std::endl;
   output << player->getScore() << std::endl;

   for (int i = 0; i < player->getPlayerHand()->getSize(); i++)
   {
      if (i < player->getPlayerHand()->getSize() - 1)
      {
         Tile *currTile = player->getPlayerHand()->get(i);
         output << currTile->getLetter() << "-" << currTile->getValue() << ", ";
      }
      else
      {
         Tile *currTile = player->getPlayerHand()->get(i);
         output << currTile->getLetter() << "-" << currTile->getValue() << std::endl;
      }
   }
}

void saveGameState(std::ofstream &output, TileBag *tileBag, Player *currentPlayer, ScrabbleBoard *scrabbleBoard)
{
   // Displays the board
   output << scrabbleBoard->saveState() << std::endl;

   for (int i = 0; i < tileBag->getSize(); i++)
   {
      if (i < tileBag->getSize() - 1)
      {
         Tile *currTile = tileBag->get(i);
         output << currTile->getLetter() << "-" << currTile->getValue() << ", ";
      }
      else
      {
         Tile *currTile = tileBag->get(i);
         output << currTile->getLetter() << "-" << currTile->getValue() << std::endl;
      }
   }
   output << currentPlayer->getName();
   // output << tileBag->getSize();
   output.close();
}

void displayGameResults(Player *player1, Player *player2)
{
   std::cout << std::endl;
   std::cout << "---Game over---" << std::endl;
   std::cout << "Score for " << player1->getName() << ": " << player1->getScore() << std::endl;
   std::cout << "Score for " << player2->getName() << ": " << player2->getScore() << std::endl;


   if (player1->getScore() > player2->getScore()) 
   {
      std::cout << "Player " << player1->getName() << " won!" << std::endl;
   }
   else if (player1->getScore() < player2->getScore())
   {
      std::cout << "Player " << player2->getName() << " won!" << std::endl;
   }
   else if (player1->getScore() == player2->getScore())
   {
      std::cout << "Draw! Both players have the same score." << std::endl;
   }
}
