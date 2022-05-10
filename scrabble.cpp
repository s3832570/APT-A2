
#include "LinkedList.h"
#include "Player.h"
#include "ScrabbleBoard.h"
#include "TileBag.h"

#include <iostream>
#include <regex>
#include <vector>
#include <fstream>

#define EXIT_SUCCESS 0

/**
 * TODO:
 * - 🟡 main menu
 *    > 1. new game ✅
 *       • display "Starting a new game" ✅
 *    > 2. load game
 *       • display "Enter the filename from which load a game"
 *       • user enters relative path and then presses enter
 *       • check file exists
 *       • check file format is correct (maybs try catch exception)
 *       • display "Scrabble game successfully loaded"
 *    > 3. show credits ✅
 *       • all student information ✅
 *    > 4. quit program ✅
 *    > user will enter number to select ✅
 *       • check number is in bounds ✅
 *
 * - 🟠 player
 *    > score ✅
 *    > hand
 *    > name ✅
 *    > update players score ✅
 *
 * - 🟠 player hand
 *    > linked list ✅
 *
 * - 🟢 tile bag
 *    linked list ✅
 *    > jumbles tile bag and pulls from front (put in "random" order) ✅
 *    > replace players tiles with new tiles from tile bag  ✅
 *       • tile must be removed from tile bag ✅
 *
 * - 🟢 linked list
 *    > add back ✅
 *    > add front ✅
 *
 * - 🟢 node
 *    constructor ✅
 *    copy constuctor ✅
 *    data (tile) ✅
 *    Node* pointer ✅
 *
 * - 🔴 tile
 *
 * - 🔴 board
 *    > A vector of vectors of tiles ✅
 *    > rows ✅
 *    > columns ✅
 *    > create empty board ✅
 *    > check placement of tile is legal
 *
 * - 🟡 {the game
 *    > ask for player names (must only contain letters) ✅
 *       • "Enter a name for player 1 (uppercase characters only)" ✅
 *         display "Let's Play!" ✅
 *    > display players' scores ✅}
 *    > display board
 *    > display player 1's hand
 *    > user prompt showing the commands they can use
 *    game always begins with player 1
 *    player can place up to 7 letters
 *    > must type "place <capital letter> at <coordinate>" (check format)
 *       > if player places 7 tiles must display "BINGO!!!" before
 *      displaying game results
 *      must type "place Done" to finish turn (check format)
 *    > show results on board
 *    > move to next players turn
 *    > player can replace ONE tile per turn
 *       • by typing "replace <letter>" (letter must be caps)
 *       • check format
 *       • check player has that tile
 *       • if tile exists in hand, place tile back in tile bag and
 *         draw new tile from tile bag (if player has two of same
 *         letter, take first instance)
 *       • replacing tile counts as their turn, move to next player
 *    > player can type "pass" to pass their turn
 *    > save game
 *       • player types "save <filename>"
 *       • display "Game successfully saved"
 *       • turn continues as normal
 *       • formatting for save file is on pg 10-11 of spec
 *    > quit game (idk if game has to save before quitting?)
 *       • no crashing :)
 *       • also quits if ^D is enterd
 *    > game ends when tile bag is empty, player has no more tiles in hand
 *      or turn passes twice
 *       • display "Game over"
 *       • display score for both players "Score for <player>: 000"
 *       • display "Player <player> won!"
 *       • display "Goodbye" and then quit game
 *
 * - PlayGame function
 *    > While tilebag != zero
 *    >
 *
 * - 🟢 load game
 *    > resume game with current player when loaded
 *
 * - user input ✅
 *    > display "Invalid Input" when input is invalid ✅
 *
 * put ✅ at start of every task completed
 * and possibly a coloured circle for who implemented? (🔴 - Alex, 🟠 - Chloe, 🟡 - Hien, 🟢 - Lachlan)
 * Just so we know who has to write about that feature
 * in the report.
 */

void mainMenu();
void newGame();
void viewCredits();
bool containsOnlyLetters(std::string name);
void inputName(std::string *name);
void playGame(TileBag *tileBag, Player *player1, Player *player2);
bool placeTiles(PlayerHand *playerHand, std::vector<std::string> commands, ScrabbleBoard *board, Player *player);
void dealPlayer(TileBag *tileBag, Player *player);

int main(void)
{
   // LinkedList* list = new LinkedList();
   // delete list;

   // std::cout << "TODO: Implement Scrabble!" << std::endl;

   // Load main menu
   mainMenu();
   

   return EXIT_SUCCESS;
}

void mainMenu()
{
   std::cout << "Welcome to Scrabble!" << std::endl;
   std::cout << "-------------------" << std::endl;

   int userMenuInput = 0;
   while (userMenuInput != 1 && userMenuInput != 4)
   {
      std::cout << "Menu" << std::endl;
      std::cout << "----" << std::endl;
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Load Game" << std::endl;
      std::cout << "3. Credits (Show student information)" << std::endl;
      std::cout << "4. Quit" << std::endl;

      std::cout << std::endl;
      std::cout << "> ";

      while ((!(std::cin >> userMenuInput) || !(userMenuInput >= 1 && userMenuInput <= 4)) && !std::cin.eof())
      {
         std::cout << "Invalid Input" << std::endl;
         std::cout << "> ";
         std::cin.clear();
         std::cin.ignore(100, '\n');
      }

      if (userMenuInput == 1)
      {
         newGame();
      }
      /**
       * TODO:
       * if (userMenuInput == 2) {
       *
       * }
       *
       */
      if (userMenuInput == 3)
      {
         viewCredits();
      }

      // TESTING FUNCTION ONLY
      if (userMenuInput == 4)
      {
         // quit
      }
   }
   std::cout << std::endl;
   std::cout << "Goodbye" << std::endl;
}

void newGame()
{
   TileBag *tileBag = new TileBag();

   // Reading in new tile bag
   std::fstream infile("ScrabbleTiles.txt");
   char letter;
   int value;
   while (infile >> letter >> value)
   {
      tileBag->addNewTile(new Tile(letter, value));
   }
   tileBag->shuffleBag();

   std::string player1Name;
   std::string player2Name;

   std::cout << std::endl;
   std::cout << "Starting a New Game" << std::endl;
   std::cout << std::endl;

   std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
   std::cout << "> ";
   inputName(&player1Name);
   Player *player1 = new Player(player1Name);
   std::cout << std::endl;

   std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
   std::cout << "> ";
   inputName(&player2Name);
   Player *player2 = new Player(player2Name);
   std::cout << std::endl;

   std::cout << "Let's Play!" << std::endl;
   std::cout << std::endl;

   playGame(tileBag, player1, player2);
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
   std::cout << "Name: Alexander Perera" << std::endl;
   std::cout << "Student ID: s3721805" << std::endl;
   std::cout << "Email: s3721805@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: Lachlan Ward" << std::endl;
   std::cout << "Student ID: s3888736" << std::endl;
   std::cout << "Email: s3888736@student.rmit.edu.au" << std::endl;
   std::cout << "----------------------------------" << std::endl;
   std::cout << std::endl;
}

void playGame(TileBag *tileBag, Player *player1, Player *player2)
{
   // Initalise Board
   ScrabbleBoard *scrabbleBoard = new ScrabbleBoard();

   // Initalise Current Player to Player 1
   Player *currentPlayer = player1;

   // Collection of all placements for players turn
   std::vector<std::string> placements;

   std::cout << "vector size: " << placements.size() << std::endl;

   // Deal players initial 7 tiles
   dealPlayer(tileBag, player1);
   dealPlayer(tileBag, player2);

   // While Tiles are still left in bag
   while (tileBag->getSize() != 0)
   {
      placements.clear();
      // Output current player name and both players scores
      std::cout << currentPlayer->getName() << ", it's your turn" << std::endl;
      std::cout << "Score for " << player1->getName() << ": " << player1->getScore() << std::endl;
      std::cout << "Score for " << player2->getName() << ": " << player2->getScore() << std::endl;

      // Output Board
      scrabbleBoard->displayBoard();

      // Displaying players hand
      std::cout << "Your hand is" << std::endl;
      for (int i = 0; i < currentPlayer->getPlayerHand()->getSize(); i++)
      {
         Tile *currTile = currentPlayer->getPlayerHand()->get(i);
         std::cout << currTile->getLetter() << "-" << currTile->getValue() << " ";
      }
      std::cout << "\n"
                << std::endl;

      bool turnIsDone = false;
      std::string command;
      std::string next;
      std::string at;
      std::string coord;

      while (turnIsDone != true)
      {
         std::cout << "> ";
         std::cin >> command;

         if (command == "place")
         {
            std::cin >> next;

            if (next == "Done")
            {
               turnIsDone = true;
            }
            else
            {
               std::cin >> at >> coord;
               std::string row;
               row.push_back(coord.at(0));
               if (containsOnlyLetters(next) && containsOnlyLetters(row) && std::isdigit(coord.at(1)))
               {
                  command = command + " " + next + " " + at + " " + coord;
                  placements.push_back(command);
               }
               else
               {
                  std::cout << "The command you entered is incorrect. Try again." << std::endl;
               }
            }
         }

         /**
          * user turn:
          * place, replace, save, pass, quit
          * user selects done (isDone = true)
          * use currentPlayer attribute for player functions
          */
      }

      if (placements.size() != 0)
      {
         if (placeTiles(currentPlayer->getPlayerHand(), placements, scrabbleBoard, currentPlayer))
         {
            // Swap Current Player After Turn has Ended
            if ((currentPlayer->getName() == player1->getName()) && (turnIsDone == true))
            {
               currentPlayer = player2;
            }
            else if ((currentPlayer->getName() == player2->getName()) && (turnIsDone == true))
            {
               currentPlayer = player1;
            }
         }
      }
   }
   delete scrabbleBoard;
}

void dealPlayer(TileBag *tileBag, Player *player)
{
   PlayerHand *playerHand = new PlayerHand();
   for (int i = 0; i < MAX_TILES; i++)
   {
      Tile *newTile = tileBag->getNewTile();
      playerHand->addTile(newTile);
      tileBag->removeTile();
   }

   player->setPlayerHand(playerHand);
}

bool placeTiles(PlayerHand *playerHand, std::vector<std::string> commands,
                ScrabbleBoard *board, Player *player)
{
   bool retVal = false;

   if (board->checkPlacement(commands))
   {
      for (std::string &command : commands)
      {
         /**
          * TODO:
          * Make sure tile is placed next to an existing tile and word goes in right direction
          * place A at A2
          */
         Tile *tileToPlace = nullptr;

         std::string letter;
         letter.push_back(command.at(6));
         std::string coord = command.substr(11, 12);

         // getting correct tile
         for (int i = 0; i < playerHand->getSize(); i++)
         {
            if (playerHand->get(i)->getLetter() == letter.at(0))
            {
               tileToPlace = playerHand->get(i);
            }
         }

         // getting row
         int row = board->findRow(coord.at(0));

         // getting column
         int col = coord.at(1) - '0';

         if (board->placeTile(tileToPlace, row, col) == false)
         {
            std::cout << "There is already a tile at " << coord << std::endl;
         }
         else
         {
            player->setScore(player->getScore() + tileToPlace->getValue());
            playerHand->removeTile(tileToPlace);
            retVal = true;
         }
      }
   }
   else
   {
      std::cout << "\n";
      std::cout << "The placement of your tiles is not legal. Try again." << std::endl;
      std::cout << "\n";
      retVal = false;
   }

   return retVal;
}
